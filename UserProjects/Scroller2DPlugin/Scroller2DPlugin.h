#ifndef Scroller2DPlugin_H
#define Scroller2DPlugin_H
#include "Scroller2DPlugin_global.h"
#include "device.h"

#include "GScroller2D.h"

/////////////////////////////////////////////////////////////////////
//! \brief The GScroller2DPlugin class implements the GDevicePlugin that provides a low pass filtered for a parameter.
/*!
*/
class Scroller2DPlugin_EXPORT GScroller2DPlugin : public GDevicePlugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Gael.GDevicePlugin/2.0")
	Q_INTERFACES(GDevicePlugin)
	G_REGISTER_PLUGIN_PROG_DEVICE(GScroller2D)

public:
	GScroller2DPlugin(QObject *parent = 0);
	~GScroller2DPlugin();

private:

};

#endif // Scroller2DPlugin_H
