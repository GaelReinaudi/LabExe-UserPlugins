#include "GPhidgetManager.h"
#include "GPhidgetManagerWidget.h"
#include "GPhidgetAdvancedServoModule.h"
#include "GPhidgetInterfaceKitModule.h"
#include "GPhidgetAnalogOutModule.h"
#include "GPhidgetTemperatureSensor1Module.h"
#include "GPhidgetTouchRotationModule.h"

#include "GPhidget21.h"

#include <QMap>
// Mapping of device type/names to LabExe Classes
QMap<QString, QString> GPhidgetManager::PhidgetMap_Name_Class;

G_REGISTER_HARD_DEVICE_CLASS(GPhidgetManager)

/////////////////////////////////////////////////////////////////////
/*! \relates GPhidgetManager
\brief GPhidgetManagerAttachHandler() is function called when a phidget gets attached. 
The phidget API knows that it has to call this function because I call this Phidget-API function:
\code PhidgetManager_set_OnAttachHandler(m_ThePhidgetManager, GPhidgetManagerAttachHandler, this); \endcode
\param:  PhidgetHandle phid : the phidget-API needed handle to a phidget
\param:  void * pPhiMan : a user pointer that I happened to be the pointer to the GPhidgetManager object that fired the event.
*////////////////////////////////////////////////////////////////////
int __stdcall GPhidgetManagerAttachHandler(PhidgetHandle phid, void* pPhiMan)
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

	GPhidgetManager* pPhidgetManager = (GPhidgetManager*)pPhiMan;
	if(pPhidgetManager->ThePhidgetManager() == 0)
		pPhidgetManager = 0;
	if(pPhidgetManager)
		pPhidgetManager->UpdateListPhidgetsModules();
	return 0;
}

/////////////////////////////////////////////////////////////////////
/*! \relates GPhidgetManager
\brief GPhidgetManagerDettachHandler() is function called when a phidget gets dettached. 
The phidget API knows that it has to call this function because I call this Phidget-API function:
\code PhidgetManager_set_OnDettachHandler(m_ThePhidgetManager, GPhidgetManagerDettachHandler, this); \endcode
\param:  PhidgetHandle phid : the phidget-API needed handle to a phidget
\param:  void * pPhiMan : a user pointer that I happened to be the pointer to the GPhidgetManager object that fired the event.
*////////////////////////////////////////////////////////////////////
int __stdcall GPhidgetManagerDetachHandler(PhidgetHandle phid, void* pPhiMan)
{
	int serialNo;
	const char *name;

	Phidget_getDeviceName (phid, &name);
	Phidget_getDeviceSerialNumber(phid, &serialNo);
	printf("%s %10d detached!\n", name, serialNo);

	GPhidgetManager* pPhidgetManager = (GPhidgetManager*)pPhiMan;
	if(pPhidgetManager->ThePhidgetManager() == 0)
		pPhidgetManager = 0;
	if(pPhidgetManager)
		pPhidgetManager->UpdateListPhidgetsModules();
	return 0;
}

/////////////////////////////////////////////////////////////////////
/*! \relates GPhidgetManager
\brief GPhidgetManagerErrorHandler() is function called when the phidget API detects an error. 
The phidget API knows that it has to call this function because I call this Phidget-API function:
\code PhidgetManager_set_OnErrorHandler(m_ThePhidgetManager, GPhidgetManagerErrorHandler, this); \endcode
\param:  PhidgetHandle phid : the phidget-API needed handle to a phidget
\param:  void * pPhiMan : a user pointer that I happened to be the pointer to the GPhidgetManager object that fired the event.
*////////////////////////////////////////////////////////////////////
int __stdcall GPhidgetManagerErrorHandler(PhidgetManagerHandle MAN, void *usrptr, int Code, const char *Description)
{
	qDebug() << "GPhidgetManagerErrorHandler: %d - %s\n", Code, Description;
	return 0;
}

GPhidgetManager::GPhidgetManager(QString uniqueIdentifierName, QObject *parent)
	: GHardDevice(uniqueIdentifierName, parent)
	,  m_ThePhidgetManager(0)
{

	PhidgetMap_Name_Class.insert("Phidget Touch Rotation", "PhidgetTouchRotation");

	Phidget_enableLogging(PHIDGET_LOG_VERBOSE, NULL);
	//create the Manager object
	PhidgetManager_create(&m_ThePhidgetManager);
	//Set the handlers to be run when the device is plugged in or opened from software, unplugged or closed from software, or generates an error.
	PhidgetManager_set_OnAttachHandler(m_ThePhidgetManager, GPhidgetManagerAttachHandler, this);
	PhidgetManager_set_OnDetachHandler(m_ThePhidgetManager, GPhidgetManagerDetachHandler, this);
	PhidgetManager_set_OnErrorHandler(m_ThePhidgetManager, GPhidgetManagerErrorHandler, this);
	//open the Manager for device connections
	//all done, cleanup in destructor
#ifndef CONNECTION_TROUGH_IP
	PhidgetManager_open(m_ThePhidgetManager);
#else
	PhidgetManager_openRemoteIP(m_ThePhidgetManager, CONNECTION_TROUGH_IP);
#endif

	// when the Phidgets list has changed, we want to create/update the corresponding GDevices.
	connect(this, SIGNAL(ListPhidgetModulesChanged()), this, SLOT(CreateNewlyDetectedPhidgetModules()));
}

GPhidgetManager::~GPhidgetManager()
{
	//...we will close the phidget and delete the object we created
	printf("Closing...\n");
	PhidgetManager_close(m_ThePhidgetManager);
	PhidgetManager_delete(m_ThePhidgetManager);
}

QString GPhidgetManager::CreateUniquePhidgetIdentifier(QString strType, int serial, QString PhidgetApiName) const {
	QString thePhidString("%1%2%3");
	if(PhidgetMap_Name_Class.contains(PhidgetApiName)){
		strType = PhidgetMap_Name_Class.value(PhidgetApiName);
	}
	return thePhidString.arg(strType).arg(PHIDGET_NAME_SERIAL_SEPARATOR).arg(serial);
}

int GPhidgetManager::GetSerialFromPhidgetIdentifier(QString strUniqueID) {
	return strUniqueID.mid(strUniqueID.lastIndexOf(PHIDGET_NAME_SERIAL_SEPARATOR) + 1).toInt();
}

QString GPhidgetManager::GetTypeFromPhidgetIdentifier(QString strUniqueID) {
	return strUniqueID.left(strUniqueID.indexOf(PHIDGET_NAME_SERIAL_SEPARATOR));
}

//! updates the list of the attached phidgets.
void GPhidgetManager::UpdateListPhidgetsModules()
{
	int serialNo, version, numDevices, i;
	const char* deviceType;
	const char* deviceName;
	PhidgetHandle *devices;
	QStringList oldList = m_ListPhidgetModules;

	m_ListPhidgetModules.clear();
	m_SerialPhidgetModules.clear();

	PhidgetManager_getAttachedDevices (m_ThePhidgetManager, &devices, &numDevices);
	for(i = 0; i < numDevices; i++)
	{	// for each device, let's get the device information.
		Phidget_getDeviceType(devices[i], &deviceType);
		Phidget_getDeviceName(devices[i], &deviceName);
		Phidget_getDeviceSerialNumber(devices[i], &serialNo);
		Phidget_getDeviceVersion(devices[i], &version);

		QString thePhidString = CreateUniquePhidgetIdentifier(deviceType, serialNo, deviceName);
		// we add the name in the list of name of phidgets
		m_ListPhidgetModules.append(thePhidString);
		// Lets add it to the map <serial, pointer>. 
		// The pointer might be 0 if it was not created. It will be created in CreatePhidgetModules().
		GDevice* pDevice = GetDeviceFromDeviceManager(thePhidString);
		if(pDevice)
			m_SerialPhidgetModules.insert(serialNo, pDevice);
	}
	PhidgetManager_freeAttachedDevicesArray(devices);

	if(oldList != m_ListPhidgetModules)
		emit ListPhidgetModulesChanged();
}

void GPhidgetManager::CreateNewlyDetectedPhidgetModules()
{
	QStringList strDevicesList = m_ListPhidgetModules;
	foreach(QString strPhidgetModule, strDevicesList) { // ex: strPhidgetModule = "PhidgetRCServo:99926"
		QString CardType = GetTypeFromPhidgetIdentifier(strPhidgetModule); // ex: CardType = "PhidgetRCServo"
		int PhidgetSerial = GetSerialFromPhidgetIdentifier(strPhidgetModule);// ex: PhidgetSerial = 99926
		// The unique name for the device here.
		QString uniqueIdentifierNameForDevice = strPhidgetModule;

		// if the device doesn't already exists then we make it
		GDevice* pDevModule = GetDeviceFromDeviceManager(uniqueIdentifierNameForDevice);
		if(!pDevModule && PhidgetSerial != 0) {
			if(CardType == "PhidgetTouchRotation") {
				pDevModule = new GPhidgetTouchRotationModule(uniqueIdentifierNameForDevice, this);
			}
			if(CardType == "PhidgetRCServo") {
				pDevModule = new GPhidgetAdvancedServoModule(uniqueIdentifierNameForDevice, this);
			}
			else if(CardType == "PhidgetInterfaceKit") {
				pDevModule = new GPhidgetInterfaceKitModule(uniqueIdentifierNameForDevice, this);
			}
			else if(CardType == "PhidgetAnalog") {
				pDevModule = new GPhidgetAnalogOutModule(uniqueIdentifierNameForDevice, this);
			}
			else if(CardType == "PhidgetTemperatureSensor") {
				pDevModule = new GPhidgetTemperatureSensor1Module(uniqueIdentifierNameForDevice, this);
			}
			// and we insert it again in m_SerialPhidgetModules to replace the null pointer with the newly created one.
			// but if we still couldn't create it, then we remove it
			if(pDevModule)
				m_SerialPhidgetModules.insert(PhidgetSerial, pDevModule);
			else {
				m_SerialPhidgetModules.remove(PhidgetSerial);
				m_ListPhidgetModules.removeOne(strPhidgetModule);
				qWarning() << "The phidget \"" << strPhidgetModule 
					<< "\" was detected but can't be created as a device." 
					<< "The LabExe might not be aware of that type of device.";
			}
		}
	}
}

GDeviceWidget* GPhidgetManager::ProvideNewDeviceGroupBox( QWidget* inWhichWidget, QBoxLayout::Direction orientation /*= QBoxLayout::LeftToRight*/ )
{
	// first, we create any newly detected phidget
	CreateNewlyDetectedPhidgetModules();
	GPhidgetManagerWidget* pWidToReturn = new GPhidgetManagerWidget(this, inWhichWidget);
	// we connect so that the GPhidgetManager updates when the phidget modules change.
	connect(this, SIGNAL(ListPhidgetModulesChanged()), pWidToReturn, SLOT(UpdateSubDevicesWidgetList()), Qt::QueuedConnection);

	PopulateDeviceWidget(pWidToReturn);
	return pWidToReturn;
}

QList<GDevice*> GPhidgetManager::SubDevices() const
{
	QList<GDevice*> listsubDev;
	// we just remove the null pointers that could be there because phidgets were detected but not yet created
	foreach(GDevice* pDev, m_SerialPhidgetModules.values())
		if(pDev)
			listsubDev.append(pDev);
	return listsubDev;
}
