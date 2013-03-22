#ifndef PLUGINPHIDGETS_H
#define PLUGINPHIDGETS_H
#include "pluginphidgets_global.h"
#include "device.h"

#include "GPhidgetManager.h"

/////////////////////////////////////////////////////////////////////
//! \brief The GPluginPhidgets class implements the GDevicePlugin.
/*!
This plugin will register several GDevice classes in the device manager in order to control modules from the company Phidgets.
*/
class PLUGINPHIDGETS_EXPORT GPluginPhidgets : public GDevicePlugin
{
	Q_OBJECT
	Q_INTERFACES(GDevicePlugin)
	G_REGISTER_PLUGIN_HARD_DEVICE(GPhidgetManager, "Phidgets Manager")

public:
	GPluginPhidgets(QObject *parent = 0);
	~GPluginPhidgets();

private:

};

#endif // PLUGINPHIDGETS_H
