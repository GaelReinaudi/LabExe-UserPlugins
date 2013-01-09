#ifndef SERIALCOMPORTPLUGIN_H
#define SERIALCOMPORTPLUGIN_H
#include "serialcomportplugin_global.h"
#include "device.h"

#include "GSerialPortController.h"

/////////////////////////////////////////////////////////////////////
//! \brief The GSerialComPortPlugin class implements the GDevicePlugin.
/*!
This plugin allows you to control the serial port
*/
class SERIALCOMPORTPLUGIN_EXPORT GSerialComPortPlugin : public GDevicePlugin
{
	Q_OBJECT
	Q_INTERFACES(GDevicePlugin)
	G_REGISTER_PLUGIN_PROG_DEVICE(GSerialPortController)

public:
	GSerialComPortPlugin(QObject *parent = 0);
	~GSerialComPortPlugin();

private:

};

#endif // SERIALCOMPORTPLUGIN_H
