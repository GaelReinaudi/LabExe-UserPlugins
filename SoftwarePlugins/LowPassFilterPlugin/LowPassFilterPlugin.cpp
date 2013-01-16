#include "LowPassFilterPlugin.h"

Q_EXPORT_PLUGIN2(GLowPassFilterPlugin, GLowPassFilterPlugin)

GLowPassFilterPlugin::GLowPassFilterPlugin(QObject *parent)
	: GDevicePlugin(parent)
{
}

GLowPassFilterPlugin::~GLowPassFilterPlugin()
{

}
