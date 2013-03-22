#ifndef GPHIDGETSENSOR_H
#define GPHIDGETSENSOR_H
#include "pluginphidgets_global.h"

#include "device.h"
#include "param.h"

/////////////////////////////////////////////////////////////////////
//! \brief The GPhidgetSensor class defines a sensor controlled through the phidget API of a phidget interface kit
/*!
The uniqueIdentifierName has to be on the form provided by GPhidgetInterfaceKitModule::CreateUniqueSensorIdentifier(int indexSensor).
*/
class PLUGINPHIDGETS_EXPORT GPhidgetSensor : public GHardDevice
{
	Q_OBJECT

public:
	GPhidgetSensor(QString uniqueIdentifierName, QObject *parent);
	~GPhidgetSensor();

protected:
	//! Reimplemented
	virtual void PopulateDeviceWidget(GDeviceWidget* theDeviceWidget);

private:
	//! Called by the module when it detected a position change
	void ModuleTriggeredValueChanged( int theValue );

private:
	//! The param holding the last measured input value
	GParamDouble m_LastMeasure;

	friend class GPhidgetInterfaceKitModule;
};

#endif // GPHIDGETSENSOR_H
