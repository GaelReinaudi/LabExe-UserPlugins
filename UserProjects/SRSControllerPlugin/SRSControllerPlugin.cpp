#include "SRSControllerPlugin.h"

Q_EXPORT_PLUGIN2(GSRSControllerPlugin, GSRSControllerPlugin)

GSRSControllerPlugin::GSRSControllerPlugin(QObject *parent)
	: GDevicePlugin(parent)
{
}

GSRSControllerPlugin::~GSRSControllerPlugin()
{

}
