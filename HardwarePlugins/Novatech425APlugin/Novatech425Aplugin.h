#ifndef Novatech425APLUGIN_H
#define Novatech425APLUGIN_H
#include "Novatech425Aplugin_global.h"
#include "device.h"

#include "GNovatech425A.h"

/////////////////////////////////////////////////////////////////////
//! \brief The GNovatech425APlugin class implements the GDevicePlugin.
/*!
This plugin allows you to control the serial port
*/
class Novatech425APLUGIN_EXPORT GNovatech425APlugin : public GDevicePlugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Gael.GDevicePlugin/2.0")
	Q_INTERFACES(GDevicePlugin)
	G_REGISTER_PLUGIN_HARD_DEVICE(GNovatech425A, "Novatech 425A")

public:
	GNovatech425APlugin(QObject *parent = 0);
	~GNovatech425APlugin();

private:

};

#endif // Novatech425APLUGIN_H
