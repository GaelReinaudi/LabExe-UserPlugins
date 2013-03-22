#ifndef GGoogleChat_H
#define GGoogleChat_H

#include "device.h"
#include "param.h"
#include <QtWebKit>

/////////////////////////////////////////////////////////////////////
//! \brief The GGoogleChat class implements a GProgDevice.
/*!
This prog device allows you to go on the web..............
*/
class GGoogleChat : public GProgDevice
{
	Q_OBJECT

public:
	GGoogleChat(QObject *parent, QString uniqueIdentifierName = "");
	~GGoogleChat();

	//! Re-implemented to erase the password in some cases
	void PopulateSettings(QSettings& inQsettings);

protected:
	//! Re-implemented
	void PopulateDeviceWidget(GDeviceWidget* theDeviceWidget);
	//! Re-implemented to connect to the page 
	virtual void LatterInitialization();

signals:
	//! send the a signal to have the view(s) login
	void LoginSignal();

private:
	//! there is somehow many loading of in the page. This function will count those and trigger only one emit SucceededLogin();
	void CountingSuccessfulLoading(); 
	int m_nLoaded;
private slots:
	//! there is somehow many loading of in the page. This function will count those and trigger only one emit SucceededLogin();
	void EventSucceededLogin(); 

private:
	//! User name
	GParamString m_UserName;
	//! Password, not parented to this device so that it doesn't get saved. Will find a way to encrypt it latter !
	GParamString m_Password;
	//! the current URL
	GParamString m_CurrentUrl;
	//! was the last login successful
	GParamBool m_LastLoginSuccessful;
	//! keep signed in by re-loging automatically at the next startup
	GParamBool m_KeepMeSignedIn;

	friend class GoogleChatWidget;
};

#endif // GGoogleChat_H
