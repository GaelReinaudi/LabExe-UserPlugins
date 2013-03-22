#ifndef PLUGINWAVELENGTHHIGHFINESSE_H
#define PLUGINWAVELENGTHHIGHFINESSE_H
#include "pluginwavelengthhighfinesse_global.h"
#include "device.h"

#include "GWavelengthMeterWS6.h"

class PLUGINWAVELENGTHHIGHFINESSE_EXPORT GPluginWavelengthHighFinesse : public GDevicePlugin
{
	Q_OBJECT
	Q_INTERFACES(GDevicePlugin)
	G_REGISTER_PLUGIN_HARD_DEVICE(GWavelengthMeterWS6, "WS-200")

public:
	GPluginWavelengthHighFinesse(QObject *parent = 0);
	~GPluginWavelengthHighFinesse();

private:

};

#endif // PLUGINWAVELENGTHHIGHFINESSE_H
