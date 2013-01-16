#include "BetterAbsorptionImagePlugin.h"

Q_EXPORT_PLUGIN2(GBetterAbsorptionImagePlugin, GBetterAbsorptionImagePlugin)

GBetterAbsorptionImagePlugin::GBetterAbsorptionImagePlugin(QObject *parent)
	: GDevicePlugin(parent)
{
	setObjectName("BetterAbsorptionImagePlugin");
}

GBetterAbsorptionImagePlugin::~GBetterAbsorptionImagePlugin()
{

}
