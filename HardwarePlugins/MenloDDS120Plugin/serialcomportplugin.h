#ifndef SERIALCOMPORTPLUGIN_H
#define SERIALCOMPORTPLUGIN_H
#include "serialcomportplugin_global.h"
#include "device.h"

#include "GMenloDDS120.h"

/////////////////////////////////////////////////////////////////////
//! \brief The GMenloDDS120Plugin class implements the GDevicePlugin.
/*!
This plugin allows you to control the serial port
*/
class SERIALCOMPORTPLUGIN_EXPORT GMenloDDS120Plugin : public GDevicePlugin
{
	Q_OBJECT
	Q_INTERFACES(GDevicePlugin)
	G_REGISTER_PLUGIN_PROG_DEVICE(GMenloDDS120)

public:
	GMenloDDS120Plugin(QObject *parent = 0);
	~GMenloDDS120Plugin();

private:

};

#endif // SERIALCOMPORTPLUGIN_H
