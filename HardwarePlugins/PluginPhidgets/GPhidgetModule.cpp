#include "GPhidgetModule.h"
#include "GPhidgetManager.h"
#include "GPhidget21.h"

/////////////////////////////////////////////////////////////////////
/*! \relates GPhidgetModule
\brief GModuleAttachHandler() is function called when a phidget gets attached. 
The phidget API knows that it has to call this function because I call this Phidget-API function:
\code Phidget_setOnAttachHandler(ThePhidgetHandle(), GModuleAttachHandler, this); \endcode
\param:  PhidgetHandle phid : the phidget-API needed handle to a phidget
\param:  void * pPhiMod : a user pointer that I happened to be the pointer to the GPhidgetModule object that fired the event.
*////////////////////////////////////////////////////////////////////
int __stdcall GModuleAttachHandler(PhidgetHandle phid, void* pPhiMod)
{
	int serialNo;
	const char *name;
	Phidget_DeviceID id;
	Phidget_DeviceClass cls;

	Phidget_getDeviceName (phid, &name);
	Phidget_getDeviceSerialNumber(phid, &serialNo);
	Phidget_getDeviceClass(phid, &cls);
	Phidget_getDeviceID(phid, &id);

	printf("%s %10d attached! (%d, %d) \n", name, serialNo, cls, id);

	GPhidgetModule* pPhidgetModule = (GPhidgetModule*)pPhiMod;
	if(pPhidgetModule && pPhidgetModule->ThePhidgetHandle() == 0)
		pPhidgetModule = 0;
	if(pPhidgetModule) {
		pPhidgetModule->m_IsAttached = true;
		QTimer::singleShot(0, pPhidgetModule, SLOT(ConfigureWhenPluggedIn()));
		emit pPhidgetModule->IsAblenessMayHaveChanged(pPhidgetModule->IsAble());
	}
	return 0;
}

/////////////////////////////////////////////////////////////////////
/*! \relates GPhidgetModule
\brief GModuleDettachHandler() is function called when a phidget gets dettached. 
The phidget API knows that it has to call this function because I call this Phidget-API function:
\code Phidget_setOnDettachHandler(ThePhidgetHandle(), GModuleDettachHandler, this); \endcode
\param:  PhidgetHandle phid : the phidget-API needed handle to a phidget
\param:  void * pPhiMod : a user pointer that I happened to be the pointer to the GPhidgetModule object that fired the event.
*////////////////////////////////////////////////////////////////////
int __stdcall GModuleDetachHandler(PhidgetHandle phid, void* pPhiMod)
{
	int serialNo;
	const char *name;

	Phidget_getDeviceName (phid, &name);
	Phidget_getDeviceSerialNumber(phid, &serialNo);
	printf("%s %10d detached!\n", name, serialNo);

	GPhidgetModule* pPhidgetModule = (GPhidgetModule*)pPhiMod;
	if(pPhidgetModule && pPhidgetModule->ThePhidgetHandle() == 0)
		pPhidgetModule = 0;
	if(pPhidgetModule) {
		pPhidgetModule->m_IsAttached = false;
		emit pPhidgetModule->IsAblenessMayHaveChanged(pPhidgetModule->IsAble());
	}

	return 0;
}

/////////////////////////////////////////////////////////////////////
/*! \relates GPhidgetModule
\brief GModuleErrorHandler() is function called when the phidget API detects an error. 
The phidget API knows that it has to call this function because I call this Phidget-API function:
\code Phidget_setOnErrorHandler(ThePhidgetHandle(), GModuleErrorHandler, this); \endcode
\param:  PhidgetHandle phid : the phidget-API needed handle to a phidget
\param:  void * pPhiMod : a user pointer that I happened to be the pointer to the GPhidgetModule object that fired the event.
*////////////////////////////////////////////////////////////////////
int __stdcall GModuleErrorHandler(PhidgetHandle ADVSERVO, void *pPhiMod, const char *Description)
{
	qDebug() << QString("GModuleErrorHandler: %1 - %2\n").arg(ErrorCode).arg(QString(Description)).toUtf8();
	return 0;
}

GPhidgetModule::GPhidgetModule(QString uniqueIdentifierName, QObject *parent)
	: GHardDevice(uniqueIdentifierName, parent)
	, m_SerialNumber(0)
	, m_IsAttached(false)
{
	m_SerialNumber = GPhidgetManager::GetSerialFromPhidgetIdentifier(UniqueSystemID());
	if(!m_SerialNumber)
		return;

	QTimer::singleShot(0, this, SLOT(CommonPhidgetInitialization()));
}

GPhidgetModule::~GPhidgetModule()
{

}

GPhidgetManager* GPhidgetModule::ParentManager() const
{
	return qobject_cast<GPhidgetManager*>(parent());
}


/////////////////////////////////////////////////////////////////////
/*!
This is fired asynchronously from the constructor so that:
- virtual functions can be called,
- the phidget handler has been created.
*////////////////////////////////////////////////////////////////////
void GPhidgetModule::CommonPhidgetInitialization()
{
	//Set the handlers to be run when the device is plugged in or opened from software, unplugged or closed from software, or generates an error.
	Phidget_setOnAttachHandler(ThePhidgetHandle(), GModuleAttachHandler, this);
	Phidget_setOnDetachHandler(ThePhidgetHandle(), GModuleDetachHandler, this);
	Phidget_setOnErrorHandler(ThePhidgetHandle(), GModuleErrorHandler, this);

	//open the device for connections
#ifndef CONNECTION_TROUGH_IP
	Phidget_open(ThePhidgetHandle(), m_SerialNumber);
#else
	Phidget_openRemoteIP((PhidgetHandle)m_ThePhidgetRCServo, m_SerialNumber, CONNECTION_TROUGH_IP);
#endif
	//get the program to wait for an advanced servo device to be attached
	Phidget_waitForAttachment(ThePhidgetHandle(), 1000);

	// call to the DelayedPhidgetInitialization()
	QTimer::singleShot(0, this, SLOT(DelayedPhidgetInitialization()));
}

bool GPhidgetModule::IsAble() const
{
	if(m_IsAttached)
		if(m_SerialNumber)
			if(ParentManager())
				return true;
	return false;
}
