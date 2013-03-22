#ifndef GPHIDGETTemperatureSensor1MODULE_H
#define GPHIDGETTemperatureSensor1MODULE_H
#include "pluginphidgets_global.h"

#include "Param/GParamDouble.h"
#include "GPhidgetModule.h"
class GPhidgetManager;
class GPhidgetSensor;

typedef struct _CPhidgetTemperatureSensor *CPhidgetTemperatureSensorHandle;
typedef struct _CPhidget *CPhidgetHandle;

#define PHIDGET_SENSOR_NUMBER_SEPARATOR (QString("-S"))
#define PHIDGET_DIGITAL_INPUT_NUMBER_SEPARATOR (QString("-DI"))
#define PHIDGET_DIGITAL_OUTPUT_NUMBER_SEPARATOR (QString("-DO"))

class PLUGINPHIDGETS_EXPORT GPhidgetTemperatureSensor1Module : public GPhidgetModule
{
	Q_OBJECT

public:
	GPhidgetTemperatureSensor1Module(QString uniqueIdentifierName, QObject *parent);
	~GPhidgetTemperatureSensor1Module();

	//! Reimplemented from GDevice to add some stuff to check in order to qualify the device as "able".
	bool IsAble() const;
// 	//! Reimplemented from GDevice
// 	QList<GDevice*> SubDevices() const { return m_Sensors + m_DigInputs + m_DigOutputs; }

protected:
	//! Reimplemented
	CPhidgetHandle TheCPhidgetHandle() const { return (CPhidgetHandle)m_TheCPhidgetTemperatureSensor1; }
	//! Reimplemented
	void ConfigureWhenPluggedIn();
	//! Reimplemented
	virtual void DelayedPhidgetInitialization();
	//! Reimplemented
	virtual void PopulateDeviceWidget(GDeviceWidget* theDeviceWidget);
	//! Called to notify a temperature change.
	void TemperatureChanged(int indexSensor, double theValue);
	//! Called to notify an ambient temperature change.
	void AmbientTemperatureChanged(double theValue);

private:
	//! Creates the sensors GDevice's
	void CreateSubDevicesSensors();

private:
	CPhidgetTemperatureSensorHandle m_TheCPhidgetTemperatureSensor1;
	int m_NumberSensors;
	GParamDouble m_Temperature;
	GParamDouble m_AmbientTemperature;

	QList<GDevice*> m_Sensors;

	friend int __stdcall TemperatureChangeHandler(CPhidgetTemperatureSensorHandle IFK, void *pPhiMod, int Index, double Value);
};

#endif // GPHIDGETTemperatureSensor1MODULE_H
