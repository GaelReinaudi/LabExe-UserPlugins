#include "GoogleChatWidget.h"
#include "GGoogleChat.h"

GoogleChatWidget::GoogleChatWidget(GGoogleChat* pGoogleChat, QWidget *parent)
	: QWidget(parent)
	, m_pUserWid(0)
	, m_pPassWid(0)
{
	m_pGoogleChat= pGoogleChat;
	if(!m_pGoogleChat)
		return;

	setupUi(this);
 	QNetworkProxyFactory::setUseSystemConfiguration(true);
 	QWebSettings::globalSettings()->setAttribute(QWebSettings::PluginsEnabled, true);
 	QWebSettings::globalSettings()->setAttribute(QWebSettings::AutoLoadImages, true);

	pLayoutUserName->addWidget(m_pGoogleChat->m_UserName.ProvideNewLabel(this));
	m_pUserWid = m_pGoogleChat->m_UserName.ProvideNewParamLineEdit(this);
	pLayoutUserName->addWidget(m_pUserWid);
	pLayoutUserName->addWidget(m_pGoogleChat->m_Password.ProvideNewLabel(this));
	m_pPassWid = m_pGoogleChat->m_Password.ProvideNewParamLineEdit(this);
	pLayoutUserName->addWidget(m_pPassWid);
	pLayoutUserName->addWidget(m_pGoogleChat->m_KeepMeSignedIn.ProvideNewParamCheckBox(this));

	connect(m_pUserWid, SIGNAL(textChanged(QString)), SLOT(adjustLoginButton()));
	connect(m_pUserWid, SIGNAL(returnPressed()), SLOT(inputPassword()));
	connect(m_pPassWid, SIGNAL(textChanged(QString)), SLOT(adjustLoginButton()));
	// connects the button and enter key to the device login, which login will trigger the login of the view(s)
	connect(m_pPassWid, SIGNAL(returnPressed()), m_pGoogleChat, SIGNAL(LoginSignal()));
	connect(loginButton, SIGNAL(clicked()), m_pGoogleChat, SIGNAL(LoginSignal()));
	// device to view login
	connect(m_pGoogleChat, SIGNAL(LoginSignal()), this, SLOT(doLogin()));

	// updates the page when the Url changes
	connect(&m_pGoogleChat->m_CurrentUrl, SIGNAL(ValueUpdated(QString)), this, SLOT(UpdateUrl()));

	pWebView->setContextMenuPolicy(Qt::NoContextMenu);

	adjustLoginButton();
	showStatus("Wait...");
	// debugging: monitoring the url
	connect(pWebView, SIGNAL(linkClicked(QUrl)), this, SLOT(EventPageChanged()));
	connect(pWebView->page(), SIGNAL(contentsChanged()), this, SLOT(EventPageChanged()));
	connect(pWebView, SIGNAL(titleChanged(QString)), this, SLOT(EventPageChanged()));
}

GoogleChatWidget::~GoogleChatWidget()
{

}

void GoogleChatWidget::adjustLoginButton()
{
	QString userName = m_pGoogleChat->m_UserName.StringValue();
	QString password = m_pGoogleChat->m_Password.StringValue();
	bool ok = !userName.isEmpty() && !password.isEmpty();
	loginButton->setEnabled(ok);
}

void GoogleChatWidget::inputPassword()
{
	m_pPassWid->setFocus();
	m_pPassWid->selectAll();
}

void GoogleChatWidget::UpdateUrl()
{
	disconnect(pWebView, 0, this, 0);
	connect(pWebView, SIGNAL(loadFinished(bool)), this, SLOT(initialPage(bool)), Qt::UniqueConnection);
	connect(pWebView, SIGNAL(loadProgress(int)), progressBar, SLOT(setValue(int)), Qt::UniqueConnection);
	// sets the page
	stackedWidget->setCurrentIndex(0);
	pWebView->setUrl(QUrl(m_pGoogleChat->m_CurrentUrl.StringValue()));

	EventPageChanged();
}

void GoogleChatWidget::initialPage(bool ok) {
	if(!QSslSocket::supportsSsl()) {
		showError("This plugin requires SSL support.");
		return;
	}

	if(ok) {
		QWebElement email = document().findFirst("#Email");
		QWebElement passwd = document().findFirst("#Passwd");
		QWebElement loginForm = document().findFirst("#gaia_loginform");
		// if we are on a page that has those elements "#Email", "#Passwd", "#gaia_loginform"
		if(!email.isNull() && !passwd.isNull() && !loginForm.isNull()) {
			disconnect(pWebView, 0, this, 0);
			// show the login form and wait for it to being filled
			ShowLoginForm();
			// informing the device that we are on the login form
			emit LoginFormDisplayed();

			// test 
			// if the password was loaded with the bench, then try to login
			// and if the last login was successful...
			if(m_pGoogleChat->m_LastLoginSuccessful)
				QTimer::singleShot(1000, this, SLOT(doLogin()));

			return;
		}
	}
	showError("SERVICE unavailable.");
//	QTimer::singleShot(1000, this, SLOT(ShowWebView()));
//	qWarning() << "initialPage";
}

void GoogleChatWidget::doLogin()
{
	QString userName = m_pGoogleChat->m_UserName.StringValue();
	QString password = m_pGoogleChat->m_Password.StringValue();
	bool ok = !userName.isEmpty() && !password.isEmpty();
	if(!ok)
		return;

	progressBar->setValue(0);
	progressBar->show();
	disconnect(pWebView, 0, this, 0);
	connect(pWebView, SIGNAL(loadFinished(bool)), this, SLOT(loginPage(bool)), Qt::UniqueConnection);
	connect(pWebView, SIGNAL(loadProgress(int)), progressBar, SLOT(setValue(int)), Qt::UniqueConnection);
	showStatus("Logging in...");

	QString userEmail = userName + "@gmail.com";

	document().findFirst("#Email").setAttribute("value", userEmail);
	document().findFirst("#Passwd").setAttribute("value", password);
	document().findFirst("#gaia_loginform").evaluateJavaScript("this.submit();");
}

void GoogleChatWidget::loginPage( bool ok )
{
	QString location = pWebView->url().toString();
// 	qWarning() << location;
	if(!ok) {
		if(location.indexOf("CheckCookie"))
			return;
		showError("Service unavailable");
		QTimer::singleShot(1000, this, SLOT(ShowWebView()));
	} 
	else {
		// check for any error message
		QWebElement  e = document().findFirst(".errormsg");
		// if no error message
		if(e.isNull()) {
			disconnect(pWebView, 0, this, 0);
			ShowWebView();
			QTimer::singleShot(500, this, SLOT(hideElements()));
			// there is somehow many login in the page. This function will count those and trigger only one emit SucceededLogin();
			// the parent widget is used to know if we use the trick in order to make a new chat for displaying the contacts in this one (see GGoogleChat class)
			// TRICK ///////////////////////////////////
			if(!parentWidget())
				QTimer::singleShot(10000, this, SLOT(deleteLater()));
			else
				m_pGoogleChat->CountingSuccessfulLoading(); 
			return;
		}

		QString err = "Unknown login failure.";
		const QString errorMessage = e.toPlainText();
		if (!errorMessage.isEmpty()) {
			err = errorMessage;
			err = err.simplified();
		}
		showError(err);
		QTimer::singleShot(1000, this, SLOT(ShowWebView()));
		QTimer::singleShot(2000, this, SIGNAL(FailedLogin()));
		m_pGoogleChat->m_LastLoginSuccessful = false;
	}
}

void GoogleChatWidget::hideElements()
{
	document().findFirst(".footer-footer").removeFromDocument();
	document().findFirst(".title-bar-bg .title-bar").removeFromDocument();
	QTimer::singleShot(10000, this, SLOT(hideElements()));
}

void GoogleChatWidget::ShowWebView()
{
	stackedWidget->setCurrentIndex(2);
}

void GoogleChatWidget::ShowLoginForm()
{
	stackedWidget->setCurrentIndex(1);
	if(!m_pGoogleChat->m_UserName.StringValue().isEmpty()) {
		inputPassword();
	}
	else {
		m_pUserWid->setFocus();
	}
//	qWarning()<<"SDFSFSFASFASFS;";
}

void GoogleChatWidget::EventPageChanged()
{ 
		theUrl = pWebView->url();
		qDebug() << theUrl;
// 		qDebug() << pWebView->page()->currentFrame()->toHtml();
}