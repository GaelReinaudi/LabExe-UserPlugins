#include "plugincameraueye.h"

GPluginCameraUEye::GPluginCameraUEye(QObject *parent /*= 0*/)
	: GDevicePlugin(parent)
{
	setObjectName("uEye Cameras");
}

GPluginCameraUEye::~GPluginCameraUEye()
{

}
