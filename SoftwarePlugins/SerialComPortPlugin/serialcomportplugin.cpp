#include "serialcomportplugin.h"

Q_EXPORT_PLUGIN2(SerialComPortPlugin, GSerialComPortPlugin)

GSerialComPortPlugin::GSerialComPortPlugin(QObject *parent)
	: GDevicePlugin(parent)
{
	setObjectName("Serial port controller");
}

GSerialComPortPlugin::~GSerialComPortPlugin()
{

}
