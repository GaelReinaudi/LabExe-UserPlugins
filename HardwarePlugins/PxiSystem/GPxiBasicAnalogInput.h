#ifndef GPXIBASICANALOGINPUT_H
#define GPXIBASICANALOGINPUT_H

#include "GPxiChannel.h"
//2011-11-22 #include "Param/GParamUpdater.h"
#include "stdafx.h"
#include "NiDAQmxTask.h"

//2011-11-22 class GDataLogger;

/////////////////////////////////////////////////////////////////////
//! \brief The GPxiBasicAnalogInput is a class derived from GPxiChannel...
/*!
in order to give it basic capabilities for inputing data using any of the PXI analog input.
It inherits GParamUpdater so that the param can be updated on demand by other classes or thread.
*/
class GPxiBasicAnalogInput : public GPxiChannel, private CNiDAQmxTask //2011-11-22, public GParamUpdater
{
	Q_OBJECT

public:
	GPxiBasicAnalogInput(QString uniqueIdentifierName, QObject* parentDevice);
	~GPxiBasicAnalogInput();
//2011-11-22	void PerformParamUpdate() {UpdateFromPhysicalInput();}

signals:
	//! Emitted with the new value when the UpdateFromPhysicalInput() is successful.
	void MeasuredValueChanged(double newValue);

protected:
	//! Reimplemented from GDevice
	virtual void PopulateDeviceWidget(GDeviceWidget* theDeviceWidget);
	//! Reimplemented from GDevice.
	virtual void PopulateContextMenu(QMenu* pTheMenu);

protected slots:
	//! Uses a CNiDAQmxAnalogSingleChannelReader in order to get an update from the physical output (e.g. the voltage on the BNC).
	//! Returns the value measured or throws a CNiDAQmxException if the NI-DAQmx driver returns an error.
	double UpdateFromPhysicalInput();

private:
	GParamDouble m_Value;
//2011-11-22	GDataLogger* m_pDataLogger;
};

#endif // GPXIBASICANALOGINPUT_H
