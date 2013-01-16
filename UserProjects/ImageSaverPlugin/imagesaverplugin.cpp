#include "imagesaverplugin.h"

Q_EXPORT_PLUGIN2(ImageSaverPlugin, GImageSaverPlugin)

GImageSaverPlugin::GImageSaverPlugin(QObject *parent)
	: GDevicePlugin(parent)
{
	setObjectName("Image saver");
}

GImageSaverPlugin::~GImageSaverPlugin()
{

}
