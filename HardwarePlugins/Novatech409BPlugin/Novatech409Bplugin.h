#ifndef Novatech409BPLUGIN_H
#define Novatech409BPLUGIN_H
#include "Novatech409Bplugin_global.h"
#include "device.h"

#include "GNovatech409B.h"

/////////////////////////////////////////////////////////////////////
//! \brief The GNovatech409BPlugin class implements the GDevicePlugin.
/*!
This plugin allows you to control the serial port
*/
class Novatech409BPLUGIN_EXPORT GNovatech409BPlugin : public GDevicePlugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Gael.GDevicePlugin/2.0")
	Q_INTERFACES(GDevicePlugin)
	G_REGISTER_PLUGIN_HARD_DEVICE(GNovatech409B, "Novatech 409B")

public:
	GNovatech409BPlugin(QObject *parent = 0);
	~GNovatech409BPlugin();

private:

};

#endif // Novatech409BPLUGIN_H
