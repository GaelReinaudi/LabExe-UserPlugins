#ifndef IMAGESAVERPLUGIN_H
#define IMAGESAVERPLUGIN_H
#include "imagesaverplugin_global.h"
#include "device.h"

#include "GImageSaver.h"

/////////////////////////////////////////////////////////////////////
//! \brief The GImageSaverPlugin class implements the GDevicePlugin.
/*!
This plugin will register the GImageSaver class in the device manager for saving images.
*/
class IMAGESAVERPLUGIN_EXPORT GImageSaverPlugin : public GDevicePlugin
{
	Q_OBJECT
	Q_INTERFACES(GDevicePlugin)
	G_REGISTER_PLUGIN_PROG_DEVICE(GImageSaver)

public:
	GImageSaverPlugin(QObject *parent = 0);
	~GImageSaverPlugin();

private:

};

#endif // IMAGESAVERPLUGIN_H
