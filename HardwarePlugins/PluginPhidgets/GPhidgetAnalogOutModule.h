#ifndef GPHIDGETANALOGOUTMODULE_H
#define GPHIDGETANALOGOUTMODULE_H
#include "pluginphidgets_global.h"

#include "GPhidgetModule.h"
class GPhidgetManager;
class GPhidgetOutput;

typedef struct _CPhidgetAnalog *CPhidgetAnalogHandle;
typedef struct _CPhidget *CPhidgetHandle;

#define PHIDGET_ANALOG_OUTPUT_NUMBER_SEPARATOR (QString("-A"))

class PLUGINPHIDGETS_EXPORT GPhidgetAnalogOutModule : public GPhidgetModule
{
	Q_OBJECT

public:
	GPhidgetAnalogOutModule(QString uniqueIdentifierName, QObject *parent);
	~GPhidgetAnalogOutModule();

	//! Reimplemented from GDevice to add some stuff to check in order to qualify the device as "able".
	bool IsAble() const;
	//! Reimplemented from GDevice
	QList<GDevice*> SubDevices() const { return m_Outputs; }
	//! Returns the output corresponding to indexOutput. 0 if not.
	GPhidgetOutput* Output( int indexOutput ) const;
	//! A function to get the index of a given output from its strUniqueID
	static int GetIndexOutputFromPhidgetOutputIdentifier(QString strUniqueID);
	//! Sets the newValue to the output corresponding to the indexOutput
	void SetNewOutputValue(int indexOutput, double newValue);

protected:
	//! Reimplemented
	CPhidgetHandle TheCPhidgetHandle() const { return (CPhidgetHandle)m_TheCPhidgetAnalog; }
	//! Reimplemented
	virtual void DelayedPhidgetInitialization();
	//! Reimplemented
	void ConfigureWhenPluggedIn();
	//! Creates the sensors GDevice's
	void CreateSubDevicesOutputs();
	//! Reimplemented
	virtual void PopulateDeviceWidget(GDeviceWidget* theDeviceWidget);

private:
	//! A function to create the name of the sensor.
	QString CreateUniqueOutputIdentifier(int indexOutput) const;

private:
	CPhidgetAnalogHandle m_TheCPhidgetAnalog;
	int m_NumberOutput;
	QList<GDevice*> m_Outputs;

};

#endif // GPHIDGETANALOGOUTMODULE_H
