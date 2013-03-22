#ifndef GPXIBASICDIGITALOUTPUT_H
#define GPXIBASICDIGITALOUTPUT_H

#include "GPxiChannel.h"
#include "Param/GParamBool.h"
#include "stdafx.h"
#include "NiDAQmxTask.h"

/////////////////////////////////////////////////////////////////////
//! \brief The GPxiBasicDigitalOutput is a class derived from GPxiChannel...
/*!
in order to give it basic capabilities for outputing data using any of the PXI analog output.
*/
class GPxiBasicDigitalOutput : public GPxiChannel, private CNiDAQmxTask
{
	Q_OBJECT

public:
	GPxiBasicDigitalOutput(QString uniqueIdentifierName, QObject* parentDevice);
	~GPxiBasicDigitalOutput();

public slots:
	//! if the value is different from the current setpoint, this UpdatePhysicalOutput() and emits SetPointChanged() if successful.
	void ChangeSetPoint(bool newValue);

protected:
	//! Reimplemented from GDevice
	virtual void PopulateDeviceWidget(GDeviceWidget* theDeviceWidget);
	//! Reimplemented from GPxiChannel to take into account the format slot/port/line
	virtual QString DefaultShortName() const;

signals:
	//! emitted when the ChangeSetPoint() was called and the UpdatePhysicalOutput() is successful.
	void SetPointChanged(bool newValue);

private:
	GParamBool m_SetPoint;
	//! Uses a CNiDAQmxDigitalSingleChannelWriter in order to update the physical output (e.g. the voltage on the BNC).
	//! Returns true when it is done or false when it throws a CNiDAQmxException if the NI-DAQmx driver returns an error.
	bool UpdatePhysicalOutput(bool newSetPoint);
};

#endif // GPXIBASICDIGITALOUTPUT_H
