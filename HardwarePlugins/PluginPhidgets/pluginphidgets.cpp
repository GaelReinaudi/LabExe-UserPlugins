#include "pluginphidgets.h"

Q_EXPORT_PLUGIN2(GPluginPhidgets, GPluginPhidgets)

GPluginPhidgets::GPluginPhidgets(QObject *parent /*= 0*/)
	: GDevicePlugin(parent)
{
	setObjectName("Phidgets");
}

GPluginPhidgets::~GPluginPhidgets()
{

}
