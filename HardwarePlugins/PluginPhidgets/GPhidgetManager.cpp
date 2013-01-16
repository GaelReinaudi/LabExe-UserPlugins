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
\code CPhidgetManager_set_OnAttach_Handler(m_TheCPhidgetManager, GPhidgetManagerAttachHandler, this); \endcode
\param:  CPhidgetHandle phid : the phidget-API needed handle to a phidget
\param:  void * pPhiMan : a user pointer that I happened to be the pointer to the GPhidgetManager object that fired the event.
*////////////////////////////////////////////////////////////////////
int __stdcall GPhidgetManagerAttachHandler(CPhidgetHandle phid, void* pPhiMan)
{
	int serialNo;
	const char *name;
	CPhidget_DeviceID id;
	CPhidget_DeviceClass cls;

	CPhidget_getDeviceName (phid, &name);
	CPhidget_getSerialNumber(phid, &serialNo);
	CPhidget_getDeviceClass(phid, &cls);
	CPhidget_getDeviceID(phid, &id);

	printf("%s %10d attached! (%d, %d) \n", name, serialNo, cls, id);

	GPhidgetManager* pPhidgetManager = (GPhidgetManager*)pPhiMan;
	if(pPhidgetManager->TheCPhidgetManager() == 0)
		pPhidgetManager = 0;
	if(pPhidgetManager)
		pPhidgetManager->UpdateListPhidgetsModules();
	return 0;
}

/////////////////////////////////////////////////////////////////////
/*! \relates GPhidgetManager
\brief GPhidgetManagerDettachHandler() is function called when a phidget gets dettached. 
The phidget API knows that it has to call this function because I call this Phidget-API function:
\code CPhidgetManager_set_OnDettach_Handler(m_TheCPhidgetManager, GPhidgetManagerDettachHandler, this); \endcode
\param:  CPhidgetHandle phid : the phidget-API needed handle to a phidget
\param:  void * pPhiMan : a user pointer that I happened to be the pointer to the GPhidgetManager object that fired the event.
*////////////////////////////////////////////////////////////////////
int __stdcall GPhidgetManagerDetachHandler(CPhidgetHandle phid, void* pPhiMan)
{
	int serialNo;
	const char *name;

	CPhidget_getDeviceName (phid, &name);
	CPhidget_getSerialNumber(phid, &serialNo);
	printf("%s %10d detached!\n", name, serialNo);

	GPhidgetManager* pPhidgetManager = (GPhidgetManager*)pPhiMan;
	if(pPhidgetManager->TheCPhidgetManager() == 0)
		pPhidgetManager = 0;
	if(pPhidgetManager)
		pPhidgetManager->UpdateListPhidgetsModules();
	return 0;
}

/////////////////////////////////////////////////////////////////////
/*! \relates GPhidgetManager
\brief GPhidgetManagerErrorHandler() is function called when the phidget API detects an error. 
The phidget API knows that it has to call this function because I call this Phidget-API function:
\code CPhidgetManager_set_OnError_Handler(m_TheCPhidgetManager, GPhidgetManagerErrorHandler, this); \endcode
\param:  CPhidgetHandle phid : the phidget-API needed handle to a phidget
\param:  void * pPhiMan : a user pointer that I happened to be the pointer to the GPhidgetManager object that fired the event.
*////////////////////////////////////////////////////////////////////
int __stdcall GPhidgetManagerErrorHandler(CPhidgetManagerHandle MAN, void *usrptr, int Code, const char *Description)
{
	qDebug() << "GPhidgetManagerErrorHandler: %d - %s\n", Code, Description;
	return 0;
}

GPhidgetManager::GPhidgetManager(QString uniqueIdentifierName, QObject *parent)
	: GHardDevice(uniqueIdentifierName, parent)
	,  m_TheCPhidgetManager(0)
{

	PhidgetMap_Name_Class.insert("Phidget Touch Rotation", "PhidgetTouchRotation");

	CPhidget_enableLogging(PHIDGET_LOG_VERBOSE, NULL);
	//create the Manager object
	CPhidgetManager_create(&m_TheCPhidgetManager);
	//Set the handlers to be run when the device is plugged in or opened from software, unplugged or closed from software, or generates an error.
	CPhidgetManager_set_OnAttach_Handler(m_TheCPhidgetManager, GPhidgetManagerAttachHandler, this);
	CPhidgetManager_set_OnDetach_Handler(m_TheCPhidgetManager, GPhidgetManagerDetachHandler, this);
	CPhidgetManager_set_OnError_Handler(m_TheCPhidgetManager, GPhidgetManagerErrorHandler, this);
	//open the Manager for device connections
	//all done, cleanup in destructor
#ifndef CONNECTION_TROUGH_IP
	CPhidgetManager_open(m_TheCPhidgetManager);
#else
	CPhidgetManager_openRemoteIP(m_TheCPhidgetManager, CONNECTION_TROUGH_IP);
#endif

	// when the Phidgets list has changed, we want to create/update the corresponding GDevices.
	connect(this, SIGNAL(ListPhidgetModulesChanged()), this, SLOT(CreateNewlyDetectedPhidgetModules()));
}

GPhidgetManager::~GPhidgetManager()
{
	//...we will close the phidget and delete the object we created
	printf("Closing...\n");
	CPhidgetManager_close(m_TheCPhidgetManager);
	CPhidgetManager_delete(m_TheCPhidgetManager);
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
	CPhidgetHandle *devices;
	QStringList oldList = m_ListPhidgetModules;

	m_ListPhidgetModules.clear();
	m_SerialPhidgetModules.clear();

	CPhidgetManager_getAttachedDevices (m_TheCPhidgetManager, &devices, &numDevices);
	for(i = 0; i < numDevices; i++)
	{	// for each device, let's get the device information.
		CPhidget_getDeviceType(devices[i], &deviceType);
		CPhidget_getDeviceName(devices[i], &deviceName);
		CPhidget_getSerialNumber(devices[i], &serialNo);
		CPhidget_getDeviceVersion(devices[i], &version);

		QString thePhidString = CreateUniquePhidgetIdentifier(deviceType, serialNo, deviceName);
		// we add the name in the list of name of phidgets
		m_ListPhidgetModules.append(thePhidString);
		// Lets add it to the map <serial, pointer>. 
		// The pointer might be 0 if it was not created. It will be created in CreatePhidgetModules().
		GDevice* pDevice = GetDeviceFromDeviceManager(thePhidString);
		if(pDevice)
			m_SerialPhidgetModules.insert(serialNo, pDevice);
	}
	CPhidgetManager_freeAttachedDevicesArray(devices);

	if(oldList != m_ListPhidgetModules)
		emit ListPhidgetModulesChanged();
}

void GPhidgetManager::CreateNewlyDetectedPhidgetModules()
{
	QStringList strDevicesList = m_ListPhidgetModules;
	foreach(QString strPhidgetModule, strDevicesList) { // ex: strPhidgetModule = "PhidgetAdvancedServo:99926"
		QString CardType = GetTypeFromPhidgetIdentifier(strPhidgetModule); // ex: CardType = "PhidgetAdvancedServo"
		int PhidgetSerial = GetSerialFromPhidgetIdentifier(strPhidgetModule);// ex: PhidgetSerial = 99926
		// The unique name for the device here.
		QString uniqueIdentifierNameForDevice = strPhidgetModule;

		// if the device doesn't already exists then we make it
		GDevice* pDevModule = GetDeviceFromDeviceManager(uniqueIdentifierNameForDevice);
		if(!pDevModule && PhidgetSerial != 0) {
			if(CardType == "PhidgetTouchRotation") {
				pDevModule = new GPhidgetTouchRotationModule(uniqueIdentifierNameForDevice, this);
			}
			if(CardType == "PhidgetAdvancedServo") {
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