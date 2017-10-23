#include "imagesaverplugin.h"

GImageSaverPlugin::GImageSaverPlugin(QObject *parent)
	: GDevicePlugin(parent)
{
	setObjectName("Image saver");
}

GImageSaverPlugin::~GImageSaverPlugin()
{

}
