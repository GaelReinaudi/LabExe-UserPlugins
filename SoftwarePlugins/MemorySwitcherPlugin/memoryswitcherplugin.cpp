#include "memoryswitcherplugin.h"

Q_EXPORT_PLUGIN2(GMemorySwitcherPlugin, GMemorySwitcherPlugin)

GMemorySwitcherPlugin::GMemorySwitcherPlugin(QObject *parent)
	: GDevicePlugin(parent)
{
	setObjectName("Memory switcher");
}

GMemorySwitcherPlugin::~GMemorySwitcherPlugin()
{

}
