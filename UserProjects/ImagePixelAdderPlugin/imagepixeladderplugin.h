#ifndef IMAGEPIXELADDERPLUGIN_H
#define IMAGEPIXELADDERPLUGIN_H
#include "imagepixeladderplugin_global.h"
#include "device.h"

#include "GImagePixelAdder.h"

/////////////////////////////////////////////////////////////////////
//! \brief The GImagePixelAdderPlugin class implements the GDevicePlugin.
/*!
This plugin will register the GImagePixelAdder in the device manager for computing the sum of the pixels of an image.
*/
class IMAGEPIXELADDERPLUGIN_EXPORT GImagePixelAdderPlugin : public GDevicePlugin
{
	Q_OBJECT
	Q_INTERFACES(GDevicePlugin)
	G_REGISTER_PLUGIN_PROG_DEVICE(GImagePixelAdder)

public:
	GImagePixelAdderPlugin(QObject *parent = 0);
	~GImagePixelAdderPlugin();

private:

};

#endif // IMAGEPIXELADDERPLUGIN_H
