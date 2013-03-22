#ifndef GWAVELENGTHMETERWS6_H
#define GWAVELENGTHMETERWS6_H
#include "pluginwavelengthhighfinesse_global.h"
#include "device.h"
#include "param.h"
#include "wlmData.h"

// Global functions
// void wavelengthChangedEvent(long Mode, long IntVal, double DblVal);

/////////////////////////////////////////////////////////////////////
//! \brief The GWavelengthMeterWS6 class encapsulate the WS6 wavelength meter.
/*!
It handles some of its functionality and can run a separate thread to measure parameters of the device. 
In that thread, when a wavelength is detected as having changed, the information is passed to 
the corresponding GWS6Channel object.

The GWavelengthMeterWS6 takes care of creating the GWS6Channel objects that will represents the channels in the program.
*/
class PLUGINWAVELENGTHHIGHFINESSE_EXPORT GWavelengthMeterWS6 : public GHardDevice
{
	Q_OBJECT

public:
	GWavelengthMeterWS6(QString uniqueIdentifierName, QObject *parent);
	~GWavelengthMeterWS6();

	//! Re-implemented
	QList<GDevice*> SubDevices() const {return m_Channels;}

protected:
	//! Re-implemented
	virtual void PopulateDeviceWidget(GDeviceWidget* theDeviceWidget);
	//! Re-implemented to check 
	void run();
	//! Create the sub-devices channel objects
	void CreateSubDevicesChannels();

signals:
	void wavelengthChanged(double newWavelength);

protected slots:
	void TheHFApiFiredAWLChangedEvent(double newWL);
	void EnableWLMonitoring(bool doMonitor);
	void EnableWLLocking(bool doLock);

private:
// 	//! The param holding the last measured input value
// 	GParamDouble m_LastMeasure;
// 	//! The param specifying if the m_LastMeasure has to be updated when the WS6 API detects a change.
// 	GParamBool m_DoMonitor;

	//! List of the sub-devices channels
	QList<GDevice*> m_Channels;
	//! bool controlling the thread
	bool m_ThreadWaitForEvents;
};

#endif // GWAVELENGTHMETERWS6_H
