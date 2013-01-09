#include "Scroller2DPlugin.h"

Q_EXPORT_PLUGIN2(GScroller2DPlugin, GScroller2DPlugin)

GScroller2DPlugin::GScroller2DPlugin(QObject *parent)
	: GDevicePlugin(parent)
{
	setObjectName("2D scroller");
}

GScroller2DPlugin::~GScroller2DPlugin()
{

}
