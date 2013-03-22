#ifndef GPHIDGETDIGITALINPUT_H
#define GPHIDGETDIGITALINPUT_H
#include "pluginphidgets_global.h"

#include "device.h"
#include "param.h"

/////////////////////////////////////////////////////////////////////
//! \brief The GPhidgetDigitalInput class defines a digital input controlled through the phidget API of a phidget interface kit
/*!
The uniqueIdentifierName has to be on the form provided by GPhidgetInterfaceKitModule::CreateUniqueDigitalInputIdentifier(int indexDigIn).
*/
class PLUGINPHIDGETS_EXPORT GPhidgetDigitalInput : public GHardDevice
{
	Q_OBJECT

public:
	GPhidgetDigitalInput(QString uniqueIdentifierName, QObject *parent);
	~GPhidgetDigitalInput();

protected:
	//! Reimplemented
	virtual void PopulateDeviceWidget(GDeviceWidget* theDeviceWidget);

private:
	//! Called by the module when it detected a position change
	void ModuleTriggeredValueChanged( int theValue );

private:
	//! The state of the input
	GParamBool m_State;
	//! The number of times the input fired up
	GParamInt m_CountSwitchTrue;

	friend class GPhidgetInterfaceKitModule;

};

#endif // GPHIDGETDIGITALINPUT_H
