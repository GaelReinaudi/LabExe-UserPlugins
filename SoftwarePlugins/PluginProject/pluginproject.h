#ifndef PLUGINPROJECT_H
#define PLUGINPROJECT_H
#include "pluginproject_global.h"
#include "device.h"

#include "GClassPluginDeviceTemplate.h"

/////////////////////////////////////////////////////////////////////
//! \brief The GPluginProject class implements the GDevicePlugin.
/*!
This plugin allows you to ..............
*/
class PLUGINPROJECT_EXPORT GPluginProject : public GDevicePlugin
{
	Q_OBJECT
	Q_INTERFACES(GDevicePlugin)
	G_REGISTER_PLUGIN_PROG_DEVICE(GClassPluginDeviceTemplate)

public:
	GPluginProject(QObject *parent = 0);
	~GPluginProject();

private:

};

#endif // PLUGINPROJECT_H
