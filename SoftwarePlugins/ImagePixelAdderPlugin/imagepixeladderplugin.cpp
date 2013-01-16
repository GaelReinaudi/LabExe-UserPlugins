#include "imagepixeladderplugin.h"

Q_EXPORT_PLUGIN2(ImagePixelAdderPlugin, GImagePixelAdderPlugin)

GImagePixelAdderPlugin::GImagePixelAdderPlugin(QObject *parent)
	: GDevicePlugin(parent)
{
	setObjectName("Image pixel adder");
}

GImagePixelAdderPlugin::~GImagePixelAdderPlugin()
{

}
