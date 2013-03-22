#ifndef ImageStackerPlugin_H
#define ImageStackerPlugin_H
#include "ImageStackerPlugin_global.h"
#include "device.h"

#include "GImageStacker.h"

/////////////////////////////////////////////////////////////////////
//! \brief The GImageStackerPlugin class implements the GDevicePlugin.
/*!
This plugin allows you to intercept images coming from a camera and computes an image that is the sum of those images.
*/
class ImageStackerPlugin_H GImageStackerPlugin : public GDevicePlugin
{
	Q_OBJECT
	Q_INTERFACES(GDevicePlugin)
	G_REGISTER_PLUGIN_PROG_DEVICE(GImageStacker)

public:
	GImageStackerPlugin(QObject *parent = 0);
	~GImageStackerPlugin();

private:

};

#endif // ImageStackerPlugin_H
