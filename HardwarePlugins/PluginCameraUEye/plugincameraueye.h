#ifndef PLUGINCAMERAUEYE_H
#define PLUGINCAMERAUEYE_H
#include "plugincameraueye_global.h"
#include "device.h"

#include "GUeyeCameraManager.h"

/////////////////////////////////////////////////////////////////////
//! \brief The GPluginCameraUEye class implements the GDevicePlugin.
/*!
This plugin will register a camera manager and allow the use of uEyencamera manager.
*/
class PLUGINCAMERAUEYE_EXPORT GPluginCameraUEye : public GDevicePlugin
{
	Q_OBJECT
	Q_INTERFACES(GDevicePlugin)
	G_REGISTER_PLUGIN_HARD_DEVICE(GUeyeCameraManager, "uEye Camera Manager")

public:
	GPluginCameraUEye(QObject *parent = 0);
	~GPluginCameraUEye();

private:

};

#endif // PLUGINCAMERAUEYE_H
