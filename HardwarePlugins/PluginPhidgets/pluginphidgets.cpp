#include "pluginphidgets.h"

GPluginPhidgets::GPluginPhidgets(QObject *parent /*= 0*/)
	: GDevicePlugin(parent)
{
	setObjectName("Phidgets");
}

GPluginPhidgets::~GPluginPhidgets()
{

}
