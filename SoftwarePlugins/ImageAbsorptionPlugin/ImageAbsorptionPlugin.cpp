#include "ImageAbsorptionPlugin.h"

Q_EXPORT_PLUGIN2(GImageAbsorptionPlugin, GImageAbsorptionPlugin)

GImageAbsorptionPlugin::GImageAbsorptionPlugin(QObject *parent)
	: GDevicePlugin(parent)
{
	setObjectName("ImageAbsorptionPlugin");
}

GImageAbsorptionPlugin::~GImageAbsorptionPlugin()
{

}
