#ifndef YoutubePlugin_H
#define YoutubePlugin_H
#include "YoutubePlugin_global.h"
#include "device.h"

#include "GYoutube.h"

/////////////////////////////////////////////////////////////////////
//! \brief The GYoutubePlugin class implements the GDevicePlugin that provides a low pass filtered for a parameter.
/*!
more...
*/
class YoutubePlugin_EXPORT GYoutubePlugin : public GDevicePlugin
{
	Q_OBJECT
	Q_INTERFACES(GDevicePlugin)
	G_REGISTER_PLUGIN_PROG_DEVICE(GYoutube)

public:
	GYoutubePlugin(QObject *parent = 0);
	~GYoutubePlugin();

private:

};

#endif // YoutubePlugin_H
