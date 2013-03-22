#ifndef GPHIDGETINTERFACEKITMODULE_H
#define GPHIDGETINTERFACEKITMODULE_H
#include "pluginphidgets_global.h"

#include "GPhidgetModule.h"
class GPhidgetManager;
class GPhidgetSensor;
class GPhidgetDigitalInput;
class GPhidgetDigitalOutput;

typedef struct _CPhidgetInterfaceKit *CPhidgetInterfaceKitHandle;

#define PHIDGET_SENSOR_NUMBER_SEPARATOR (QString("-S"))
#define PHIDGET_DIGITAL_INPUT_NUMBER_SEPARATOR (QString("-DI"))
#define PHIDGET_DIGITAL_OUTPUT_NUMBER_SEPARATOR (QString("-DO"))

class PLUGINPHIDGETS_EXPORT GPhidgetInterfaceKitModule : public GPhidgetModule
{
	Q_OBJECT

public:
	GPhidgetInterfaceKitModule(QString uniqueIdentifierName, QObject *parent);
	~GPhidgetInterfaceKitModule();

	//! Reimplemented from GDevice to add some stuff to check in order to qualify the device as "able".
	bool IsAble() const;
	//! Reimplemented from GDevice
	QList<GDevice*> SubDevices() const { return m_Sensors + m_DigInputs + m_DigOutputs; }
	//! Returns the sensor corresponding to indexSensor. 0 if not.
	GPhidgetSensor* Sensor( int indexSensor ) const;
	//! Returns the digital input corresponding to indexDigIn. 0 if not.
	GPhidgetDigitalInput* DigitalInput( int indexDigIn );
	//! Returns the digital output corresponding to indexDigOut. 0 if not.
	GPhidgetDigitalOutput* DigitalOutput( int indexDigOut );

protected:
	//! Reimplemented
	CPhidgetHandle TheCPhidgetHandle() const { return (CPhidgetHandle)m_TheCPhidgetInterfaceKit; }
	//! Reimplemented
	void ConfigureWhenPluggedIn();
	//! Reimplemented
	virtual void DelayedPhidgetInitialization();
	//! Reimplemented
	virtual void PopulateDeviceWidget(GDeviceWidget* theDeviceWidget);
	//! Called by the OnSensorChange_Handler.
	virtual void TriggeredSensorValueChanged(int indexSensor, int theValue);
	//! Called by the OnInputChange_Handler.
	virtual void TriggeredDigitalInputValueChanged(int indexDigIn, bool theValue);
	//! Called by the OnOutputChange_Handler.
	virtual void TriggeredDigitalOutputValueChanged(int indexDigOut, bool theValue);

private:
	//! Creates the sensors GDevice's
	void CreateSubDevicesSensors();
	//! Creates the digital input GDevice's
	void CreateSubDevicesDigitalInput();
	//! Creates the digital output GDevice's
	void CreateSubDevicesDigitalOutput();
	//! A function to create the name of the sensors.
	QString CreateUniqueSensorIdentifier(int indexSensor) const;
	//! A function to create the name of the digital inputs.
	QString CreateUniqueDigitalInputIdentifier( int indexDigIn );
	//! A function to create the name of the digital outputs.
	QString CreateUniqueDigitalOutputIdentifier( int indexDigOut );

private:
	CPhidgetInterfaceKitHandle m_TheCPhidgetInterfaceKit;
	int m_NumberSensors;
	int m_NumberDigitalInputs;
	int m_NumberDigitalOutputs;
	QList<GDevice*> m_Sensors;
	QList<GDevice*> m_DigInputs;
	QList<GDevice*> m_DigOutputs;

	friend int __stdcall SensorValueChangeHandler(CPhidgetInterfaceKitHandle IFK, void *pPhiMod, int Index, int Value);
	friend int __stdcall DigitalInputValueChangeHandler(CPhidgetInterfaceKitHandle IFK, void *pPhiMod, int Index, int Value);
	friend int __stdcall DigitalOutputValueChangeHandler(CPhidgetInterfaceKitHandle IFK, void *pPhiMod, int Index, int Value);
};

#endif // GPHIDGETINTERFACEKITMODULE_H
