#include "pluginproject.h"

Q_EXPORT_PLUGIN2(GPluginProject, GPluginProject)

GPluginProject::GPluginProject(QObject *parent)
	: GDevicePlugin(parent)
{
	setObjectName("PluginProject");
}

GPluginProject::~GPluginProject()
{

}
