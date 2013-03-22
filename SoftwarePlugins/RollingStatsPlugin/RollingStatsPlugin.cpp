#include "RollingStatsPlugin.h"

Q_EXPORT_PLUGIN2(GRollingStatsPlugin, GRollingStatsPlugin)

GRollingStatsPlugin::GRollingStatsPlugin(QObject *parent)
	: GDevicePlugin(parent)
{
}

GRollingStatsPlugin::~GRollingStatsPlugin()
{

}
