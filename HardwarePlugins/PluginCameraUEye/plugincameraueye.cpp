#include "plugincameraueye.h"

Q_EXPORT_PLUGIN2(GPluginCameraUEye, GPluginCameraUEye)

GPluginCameraUEye::GPluginCameraUEye(QObject *parent /*= 0*/)
	: GDevicePlugin(parent)
{
	setObjectName("uEye Cameras");
}

GPluginCameraUEye::~GPluginCameraUEye()
{

}
