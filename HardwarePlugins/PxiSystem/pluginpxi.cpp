#include "pluginpxi.h"

Q_EXPORT_PLUGIN2(GPluginPXI, GPluginPXI)

GPluginPXI::GPluginPXI(QObject *parent /*= 0*/)
	: GDevicePlugin(parent)
{
	setObjectName("PXI");
}

GPluginPXI::~GPluginPXI()
{

}
