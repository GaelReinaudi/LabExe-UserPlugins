#ifndef GoogleChatPlugin_H
#define GoogleChatPlugin_H
#include "GoogleChatPlugin_global.h"
#include "device.h"

#include "GGoogleChat.h"

/////////////////////////////////////////////////////////////////////
//! \brief The GGoogleChatPlugin class implements the GDevicePlugin.
/*!
This plugin allows you to ..............
*/
class GoogleChatPlugin_EXPORT GGoogleChatPlugin : public GDevicePlugin
{
	Q_OBJECT
	Q_INTERFACES(GDevicePlugin)
	G_REGISTER_PLUGIN_PROG_DEVICE(GGoogleChat)

public:
	GGoogleChatPlugin(QObject *parent = 0);
	~GGoogleChatPlugin();

private:

};

#endif // GoogleChatPlugin_H
