#include "serialcomportplugin.h"

GSerialComPortPlugin::GSerialComPortPlugin(QObject *parent)
	: GDevicePlugin(parent)
{
	setObjectName("Serial port controller");
}

GSerialComPortPlugin::~GSerialComPortPlugin()
{

}
