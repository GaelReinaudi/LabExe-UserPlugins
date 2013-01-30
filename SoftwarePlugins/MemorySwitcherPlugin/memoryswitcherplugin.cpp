#include "memoryswitcherplugin.h"

GMemorySwitcherPlugin::GMemorySwitcherPlugin(QObject *parent)
	: GDevicePlugin(parent)
{
	setObjectName("Memory switcher");
}

GMemorySwitcherPlugin::~GMemorySwitcherPlugin()
{

}
