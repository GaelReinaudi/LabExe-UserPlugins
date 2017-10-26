#include "serialcomportplugin.h"

Q_EXPORT_PLUGIN2(SerialComPortPlugin, GSerialComPortPlugin)

GSerialComPortPlugin::GSerialComPortPlugin(QObject *parent)
	: GDevicePlugin(parent)
{
	setObjectName("Novatech 409B");
}

GSerialComPortPlugin::~GSerialComPortPlugin()
{

}
