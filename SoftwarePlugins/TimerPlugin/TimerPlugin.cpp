#include "TimerPlugin.h"

Q_EXPORT_PLUGIN2(GTimerPlugin, GTimerPlugin)

GTimerPlugin::GTimerPlugin(QObject *parent)
	: GDevicePlugin(parent)
{
}

GTimerPlugin::~GTimerPlugin()
{

}
