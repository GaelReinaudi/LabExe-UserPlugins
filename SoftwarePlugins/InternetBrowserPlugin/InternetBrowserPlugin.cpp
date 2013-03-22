#include "InternetBrowserPlugin.h"

Q_EXPORT_PLUGIN2(GInternetBrowserPlugin, GInternetBrowserPlugin)

GInternetBrowserPlugin::GInternetBrowserPlugin(QObject *parent)
	: GDevicePlugin(parent)
{
	setObjectName("Internet Browser Plugin");
}

GInternetBrowserPlugin::~GInternetBrowserPlugin()
{

}
