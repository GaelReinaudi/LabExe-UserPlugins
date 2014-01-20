#ifndef GOOGLECHATWIDGET_H
#define GOOGLECHATWIDGET_H

#include "Device/GDeviceWidget.h"
#include "ui_GoogleChatWidget.h"
#include <QtWebKit>

class GGoogleChat;

class GoogleChatWidget : public QWidget, public Ui::GoogleChatWidget
{
	Q_OBJECT

public:
	GoogleChatWidget(GGoogleChat* pGoogleChat, QWidget *parent);
	~GoogleChatWidget();

protected:
	void showStatus(const QString &msg) {statusLabel->setText(msg);	stackedWidget->setCurrentIndex(0);}
	void showError(const QString &msg) {progressBar->hide();	showStatus(QString("Error: %1").arg(msg));}
	QWebElement document() const {return pWebView->page()->mainFrame()->documentElement();}

private slots:
	//! makes the login button enabled or disabled
	void adjustLoginButton();
	//! Focuses on the password if the username is not empty
	void inputPassword();
	//! updates the page accordingly to the GGoogleChat device
	void UpdateUrl();
	//! 
	void initialPage(bool ok);
	void doLogin();
	void loginPage(bool ok);
	void ShowWebView();
	void ShowLoginForm();
	void hideElements();
	//! to debug this slot intercepts when the page changes
	void EventPageChanged();

signals:
	//! Emitted when the login form is displayed and the program is waiting for some fill-in and submitting.
	void LoginFormDisplayed();
	//! Emitted when the login failed 
	void FailedLogin();
// 	//! Emitted when the login succeeded. Might be emitted several times since the page loads several times. 
// 	void SucceededLogin();

private:
	//! pointer to the GoogleChat device
	GGoogleChat* m_pGoogleChat;
	//! pointer to the password and username widgets to be able to set the focus to it
	QLineEdit *m_pPassWid, *m_pUserWid;
	QUrl theUrl;
	friend class GGoogleChat;
};

#endif // GOOGLECHATWIDGET_H
