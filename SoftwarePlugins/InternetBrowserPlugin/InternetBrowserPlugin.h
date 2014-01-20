#ifndef InternetBrowserPlugin_H
#define InternetBrowserPlugin_H
#include "InternetBrowserPlugin_global.h"
#include "device.h"

#include "GInternetBrowser.h"

/////////////////////////////////////////////////////////////////////
//! \brief The GInternetBrowserPlugin class implements the GDevicePlugin.
/*!
This plugin allows you to ..............
*/
class InternetBrowserPlugin_EXPORT GInternetBrowserPlugin : public GDevicePlugin
{
	Q_OBJECT
	Q_INTERFACES(GDevicePlugin)
	G_REGISTER_PLUGIN_PROG_DEVICE(GInternetBrowser)

public:
	GInternetBrowserPlugin(QObject *parent = 0);
	~GInternetBrowserPlugin();

private:

};

#endif // InternetBrowserPlugin_H
