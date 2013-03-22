#ifndef GWS6CHANNEL_H
#define GWS6CHANNEL_H
#include "pluginwavelengthhighfinesse_global.h"

#include "device.h"
#include "param.h"

class GWavelengthMeterWS6;

/////////////////////////////////////////////////////////////////////
//! \brief The GWS6Channel class encapsulates methods relative to the use of a channel of the WS6 wavelength meter controlled through the WS6 API.
/*!
It receives updates on the value of the wavelength from its parent GWavelengthMeterWS6 object.
*/
class PLUGINWAVELENGTHHIGHFINESSE_EXPORT GWS6Channel : public GHardDevice
{
	Q_OBJECT

public:
	GWS6Channel(QString uniqueIdentifierName, QObject *parent);
	~GWS6Channel();

	//! Called by the parent GWavelengthMeterWS6 when a wavelength has changed
	void IncomingUpdate( double newWaveLength );

protected:
	//! Re-implemented
	virtual void PopulateDeviceWidget(GDeviceWidget* theDeviceWidget);

private:
	//! The param holding the last measured input value
	GParamDouble m_LastMeasure;
	//! The param specifying if the m_LastMeasure has to be updated when the WS6 API detects a change.
	GParamBool m_DoMonitor;

};

#endif // GWS6CHANNEL_H
