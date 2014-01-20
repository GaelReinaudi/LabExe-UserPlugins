#include "GGoogleChat.h"
#include "GoogleChatWidget.h"

#define GOOGLECHAT_URL "http://talkgadget.google.com/talkgadget/m"
//#define GOOGLECHAT_URL "https://talkgadget.google.com/talkgadget/popout"

GGoogleChat::GGoogleChat(QObject *parent, QString uniqueIdentifierName /* = "" */)
	: GProgDevice(parent, uniqueIdentifierName)
	, m_nLoaded(0)
	, m_UserName("Google username:", this)
	, m_Password("Password", this, GParam::HiddenText)
	, m_CurrentUrl("Current Url", this)
	, m_LastLoginSuccessful("Successful last login", this)
	, m_KeepMeSignedIn("Keep me signed at next startup !password not encrypted for now!", this)
{
	m_CurrentUrl = GOOGLECHAT_URL;
}

GGoogleChat::~GGoogleChat()
{
}

void GGoogleChat::PopulateSettings( QSettings& inQsettings )
{
	if(!m_KeepMeSignedIn)
		m_Password = "";
	GProgDevice::PopulateSettings(inQsettings);
}

void GGoogleChat::PopulateDeviceWidget(GDeviceWidget* theDeviceWidget )
{
	// a form layout
 	QBoxLayout* pLay = new QVBoxLayout();
	theDeviceWidget->AddSubLayout(pLay);
	GoogleChatWidget* pWid = new GoogleChatWidget(this, theDeviceWidget);
	pLay->addWidget(pWid);

	// connects so that on failure we re-try
	connect(pWid, SIGNAL(FailedLogin()), this, SLOT(LatterInitialization()));
}

void GGoogleChat::LatterInitialization()
{
	m_CurrentUrl = GOOGLECHAT_URL;
}

void GGoogleChat::CountingSuccessfulLoading()
{
	m_nLoaded++;
	if(m_nLoaded == 1)
		QTimer::singleShot(1000, this, SLOT(EventSucceededLogin()));
}

void GGoogleChat::EventSucceededLogin()
{
	qDebug() << "Loaded" << m_nLoaded;
	m_nLoaded = 0;
	m_LastLoginSuccessful = true;

//return;

	// TRICK ///////////////////////////////////
	// Try to find a trick to load another chat so that the contact appears in the first one (Bug at Google)
	GoogleChatWidget* pobj = new GoogleChatWidget(this, 0);
	pobj->UpdateUrl();
	QTimer::singleShot(5000, pobj, SLOT(doLogin()));
	// TRICK ///////////////////////////////////
}