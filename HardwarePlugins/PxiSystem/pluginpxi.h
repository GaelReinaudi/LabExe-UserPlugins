#ifndef PLUGINPXI_H
#define PLUGINPXI_H
#include "pxilabexe_global.h"
#include "device.h"

#include "GPxiSystem.h"

/////////////////////////////////////////////////////////////////////
//! \brief The GPluginPXI class implements the GDevicePlugin.
/*!
This plugin will register several GDevice classes in the device manager in order to control modules of the PXI system.
*/
class PXILABEXE_EXPORT GPluginPXI : public GDevicePlugin
{
	Q_OBJECT
	Q_INTERFACES(GDevicePlugin)
	G_REGISTER_PLUGIN_HARD_DEVICE(GPxiSystem, "PXI system")

public:
	GPluginPXI(QObject *parent = 0);
	~GPluginPXI();

private:

};

#endif // PLUGINPXI_H
