#ifndef GPHIDGETMANAGER_H
#define GPHIDGETMANAGER_H
#include "pluginphidgets_global.h"

#include "device.h"
typedef struct _CPhidgetManager *CPhidgetManagerHandle;

//#define CONNECTION_TROUGH_IP "128.59.171.181", 5800, "srybex"

#define PHIDGET_NAME_SERIAL_SEPARATOR (QString(":"))

/////////////////////////////////////////////////////////////////////
//! \brief The GPhidgetManager class encapsulate a Phidget manager (from the phidget API).
/*!
It handles some phidget manager's events like:
- GPhidgetManagerAttachHandler() is function called when a phidget gets attached. The phidget API 
knows that it has to call this function because I call this Phidget-API function:
\code CPhidgetManager_set_OnAttach_Handler(m_TheCPhidgetManager, GPhidgetManagerAttachHandler, this); \endcode
- GPhidgetManagerErrorHandler() is function called when the phidget API detects an error. The phidget API 
knows that it has to call this function because I call this Phidget-API function:
\code CPhidgetManager_set_OnError_Handler(m_TheCPhidgetManager, GPhidgetManagerErrorHandler, this); \endcode

It derives fron GDevice so that it can provide a widget with a list of the phidget modules.
It defines the list of sub devices (the modules) that will be used for display on a GDeviceShelf.
*/
class PLUGINPHIDGETS_EXPORT GPhidgetManager : public GHardDevice
{
	Q_OBJECT

public:
	GPhidgetManager(QString uniqueIdentifierName, QObject *parent);
	~GPhidgetManager();

	CPhidgetManagerHandle TheCPhidgetManager() const { return m_TheCPhidgetManager; }
	void UpdateListPhidgetsModules();
	//! Reimplemented from GDevice in order to provide a special kind of widget: GPhidgetManagerWidget.
	virtual GDeviceWidget* ProvideNewDeviceGroupBox(QWidget* inWhichWidget, QBoxLayout::Direction orientation = QBoxLayout::LeftToRight);
	//! Reimplemented from GDevice
	QList<GDevice*> SubDevices() const;

	//! A function to get the serial number from the name of the phidgets modules
	static int GetSerialFromPhidgetIdentifier(QString strUniqueID);
	//! A function to get the type from the name of the phidgets modules
	static QString GetTypeFromPhidgetIdentifier(QString strUniqueID);

protected slots:
	void CreateNewlyDetectedPhidgetModules();

protected:
	//! Reimplemented
	virtual void PopulateDeviceWidget(GDeviceWidget* theDeviceWidget ) {}
	void LatterInitialization(){
		GHardDevice::LatterInitialization();
		UpdateListPhidgetsModules();
	}

signals:
	//! Create the newly detected phidget modules, I.E. the one newly obtained by UpdateListPhidgetsModules().
	void ListPhidgetModulesChanged();

private:
	//! A function to create the name of the phidgets modules. We name the device like that for ex: "PhidgetAdvancedServo:9926"
	QString CreateUniquePhidgetIdentifier(QString strType, int serial, QString PhidgetApiName) const;

private:
	//! used to map the device name from the phidget API to a class name in LabExe
	static QMap<QString, QString> PhidgetMap_Name_Class;

	//! The phidget-API handle to the phidget
	CPhidgetManagerHandle m_TheCPhidgetManager;
	//! list of the modules names
	QStringList m_ListPhidgetModules;
	//! map from modules serial number to their name
	QMap<int, GDevice*> m_SerialPhidgetModules;

	friend class GPhidgetManagerWidget;
};

#endif // GPHIDGETMANAGER_H
