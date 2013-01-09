#include "TextLoaderPlugin.h"

Q_EXPORT_PLUGIN2(GTextLoaderPlugin, GTextLoaderPlugin)

GTextLoaderPlugin::GTextLoaderPlugin(QObject *parent)
	: GDevicePlugin(parent)
{
}

GTextLoaderPlugin::~GTextLoaderPlugin()
{

}
