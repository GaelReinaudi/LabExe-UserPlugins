#ifndef MEMORYSWITCHERPLUGIN_H
#define MEMORYSWITCHERPLUGIN_H
#include "memoryswitcherplugin_global.h"
#include "device.h"

#include "GBasicParamSwitcher.h"

/////////////////////////////////////////////////////////////////////
//! \brief The GMemorySwitcherPlugin class implements the GDevicePlugin.
/*!
This plugin will register the GBasicParamSwitcher in the device manager for allowing switching of a parameters value.
*/
class MEMORYSWITCHERPLUGIN_EXPORT GMemorySwitcherPlugin : public GDevicePlugin
{
	Q_OBJECT
	Q_INTERFACES(GDevicePlugin)
	G_REGISTER_PLUGIN_PROG_DEVICE(GBasicParamSwitcher)

public:
	GMemorySwitcherPlugin(QObject *parent = 0);
	~GMemorySwitcherPlugin();

private:

};

#endif // MEMORYSWITCHERPLUGIN_H
