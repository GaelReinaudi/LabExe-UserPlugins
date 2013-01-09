#include "LockingSlapperPlugin.h"

Q_EXPORT_PLUGIN2(GLockingSlapperPlugin, GLockingSlapperPlugin)

GLockingSlapperPlugin::GLockingSlapperPlugin(QObject *parent)
	: GDevicePlugin(parent)
{
}

GLockingSlapperPlugin::~GLockingSlapperPlugin()
{

}
