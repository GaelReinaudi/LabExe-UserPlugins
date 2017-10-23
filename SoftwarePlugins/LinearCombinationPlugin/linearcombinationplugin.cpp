#include "stdafx.h"
#include "linearcombinationplugin.h"

GLinearCombinationPlugin::GLinearCombinationPlugin(QObject *parent)
	: GDevicePlugin(parent)
{
	setObjectName("Linear combination");
}

GLinearCombinationPlugin::~GLinearCombinationPlugin()
{

}
