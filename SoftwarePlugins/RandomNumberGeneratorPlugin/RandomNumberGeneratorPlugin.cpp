#include "RandomNumberGeneratorPlugin.h"

GRandomNumberGeneratorPlugin::GRandomNumberGeneratorPlugin(QObject *parent)
	: GDevicePlugin(parent)
{
	setObjectName("RandomNumberGeneratorPlugin");
}

GRandomNumberGeneratorPlugin::~GRandomNumberGeneratorPlugin()
{

}
