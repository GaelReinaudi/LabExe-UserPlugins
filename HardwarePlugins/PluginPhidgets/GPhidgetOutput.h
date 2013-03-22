#ifndef GPHIDGETOUTPUT_H
#define GPHIDGETOUTPUT_H
#include "pluginphidgets_global.h"

#include "device.h"
#include "param.h"

class GPhidgetAnalogOutModule;

/////////////////////////////////////////////////////////////////////
//! \brief The GPhidgetOutput class defines an analog output controlled through the phidget API of a phidget 4 analog output
/*!
The uniqueIdentifierName has to be on the form provided by GPhidgetAnalogOutModule::CreateUniqueOutputIdentifier(int indexOutput).
*/
class PLUGINPHIDGETS_EXPORT GPhidgetOutput : public GHardDevice
{
	Q_OBJECT

public:
	GPhidgetOutput(QString uniqueIdentifierName, QObject *parent);
	~GPhidgetOutput();

	//! returns the current value of the output GParamDouble
	double OutputValue() { return m_OutValue; }
	//! returns the index of this output in the parent Module. -1 if problem.
	int IndexOutput() const;

public slots:
	//! Updatets the output of the phidget
	void SetOutputValue( double newValue );
	//! Reimplemented to add some stuff to check in order to qualify the device as "able".
	virtual bool IsAble() const;

protected:
	//! Reimplemented
	virtual void PopulateDeviceWidget(GDeviceWidget* theDeviceWidget);
	//! returns the parent Module if there is one.
	GPhidgetAnalogOutModule* ParentModule() const;

private:
	//! The param holding the output value
	GParamDouble m_OutValue;
	friend class GPhidgetAnalogOutModule;
};

#endif // GPHIDGETOUTPUT_H
