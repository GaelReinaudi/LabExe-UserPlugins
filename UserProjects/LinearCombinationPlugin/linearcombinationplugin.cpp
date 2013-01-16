#include "stdafx.h"
#include "linearcombinationplugin.h"

Q_EXPORT_PLUGIN2(GLinearCombinationPlugin, GLinearCombinationPlugin)
GLinearCombinationPlugin::GLinearCombinationPlugin(QObject *parent)
	: GDevicePlugin(parent)
{
	setObjectName("Linear combination");
}

GLinearCombinationPlugin::~GLinearCombinationPlugin()
{

}
