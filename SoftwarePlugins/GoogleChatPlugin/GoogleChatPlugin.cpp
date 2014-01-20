#include "GoogleChatPlugin.h"

Q_EXPORT_PLUGIN2(GGoogleChatPlugin, GGoogleChatPlugin)

GGoogleChatPlugin::GGoogleChatPlugin(QObject *parent)
	: GDevicePlugin(parent)
{
	setObjectName("Google Chat Plugin");
}

GGoogleChatPlugin::~GGoogleChatPlugin()
{

}
