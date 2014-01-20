#include "DropObserverPlugin.h"

Q_EXPORT_PLUGIN2(GDropObserverPlugin, GDropObserverPlugin)

GDropObserverPlugin::GDropObserverPlugin(QObject *parent)
	: GDevicePlugin(parent)
{
	setObjectName("Drop Observer Plugin");
}

GDropObserverPlugin::~GDropObserverPlugin()
{

}
