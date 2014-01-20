#include "RandomNumberGeneratorPlugin.h"

Q_EXPORT_PLUGIN2(GRandomNumberGeneratorPlugin, GRandomNumberGeneratorPlugin)

GRandomNumberGeneratorPlugin::GRandomNumberGeneratorPlugin(QObject *parent)
	: GDevicePlugin(parent)
{
	setObjectName("RandomNumberGeneratorPlugin");
}

GRandomNumberGeneratorPlugin::~GRandomNumberGeneratorPlugin()
{

}
