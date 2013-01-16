#include "ImageStackerPlugin.h"

Q_EXPORT_PLUGIN2(GImageStackerPlugin, GImageStackerPlugin)

GImageStackerPlugin::GImageStackerPlugin(QObject *parent)
	: GDevicePlugin(parent)
{
}

GImageStackerPlugin::~GImageStackerPlugin()
{

}
