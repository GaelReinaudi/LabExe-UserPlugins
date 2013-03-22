#include "EmailMessagerPlugin.h"

Q_EXPORT_PLUGIN2(GEmailMessagerPlugin, GEmailMessagerPlugin)

GEmailMessagerPlugin::GEmailMessagerPlugin(QObject *parent)
	: GDevicePlugin(parent)
{
}

GEmailMessagerPlugin::~GEmailMessagerPlugin()
{

}
