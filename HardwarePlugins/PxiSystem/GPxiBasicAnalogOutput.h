#ifndef GPxiBasicAnalogOutput_H
#define GPxiBasicAnalogOutput_H

#include "GPxiChannel.h"
#include "stdafx.h"
#include "NiDAQmxTask.h"

/////////////////////////////////////////////////////////////////////
//! \brief The GPxiBasicAnalogOutput is a class derived from GPxiChannel...
/*!
in order to give it basic capabilities for outputing data using any of the PXI analog output.
*/
class GPxiBasicAnalogOutput : public GPxiChannel, private CNiDAQmxTask
{
	Q_OBJECT

public:
	GPxiBasicAnalogOutput(QString uniqueIdentifierName, QObject* parentDevice);
	~GPxiBasicAnalogOutput();

public slots:
	//! if the value is different from the current setpoint, this UpdatePhysicalOutput() and emits SetPointChanged() if successful.
	void ChangeSetPoint(double newValue);

protected:
	//! Reimplemented from GDevice
	virtual void PopulateDeviceWidget(GDeviceWidget* theDeviceWidget);

signals:
	//! emitted when the ChangeSetPoint() was called and the UpdatePhysicalOutput() is successful.
	void SetPointChanged(double newValue);

private:
	GParamDouble m_SetPoint;
	//! Uses a CNiDAQmxAnalogSingleChannelWriter in order to update the physical output (e.g. the voltage on the BNC).
	//! Returns true when it is done or false when it throws a CNiDAQmxException if the NI-DAQmx driver returns an error.
	bool UpdatePhysicalOutput(double newSetPoint);
};

#endif // GPxiBasicAnalogOutput_H
