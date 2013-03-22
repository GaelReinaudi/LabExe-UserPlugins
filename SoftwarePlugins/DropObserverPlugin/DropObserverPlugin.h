#ifndef PLUGINPROJECT_H
#define PLUGINPROJECT_H
#include "DropObserverPlugin_global.h"
#include "device.h"

#include "GDropObserver.h"

/////////////////////////////////////////////////////////////////////
//! \brief The GDropObserverPlugin class implements the GDevicePlugin.
/*!
This plugin allows you to ..............
*/
class PLUGINPROJECT_EXPORT GDropObserverPlugin : public GDevicePlugin
{
	Q_OBJECT
	Q_INTERFACES(GDevicePlugin)
	G_REGISTER_PLUGIN_PROG_DEVICE(GDropObserver)

public:
	GDropObserverPlugin(QObject *parent = 0);
	~GDropObserverPlugin();

private:

};

#endif // PLUGINPROJECT_H
