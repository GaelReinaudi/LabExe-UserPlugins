#ifndef Scroller2DPlugin_H
#define Scroller2DPlugin_H
#include "Scroller2DPlugin_global.h"
#include "device.h"

#include "GScroller2D.h"

/////////////////////////////////////////////////////////////////////
//! \brief The GScroller2DPlugin class implements the GDevicePlugin that provides a low pass filtered for a parameter.
/*!
This plugin allows you to define an input parameter by drag-and-dropping it in a param-bucket. 
When the input is updated, the average over the past n values is calculated and sent to 
an output param-bucket. n is defined by a spin-box.
If there are not yet n values in the past history of the parameter, the average is made on all existing data. 
The reset button clears the history of the parameter.
*/
class Scroller2DPlugin_EXPORT GScroller2DPlugin : public GDevicePlugin
{
	Q_OBJECT
	Q_INTERFACES(GDevicePlugin)
	G_REGISTER_PLUGIN_PROG_DEVICE(GScroller2D)

public:
	GScroller2DPlugin(QObject *parent = 0);
	~GScroller2DPlugin();

private:

};

#endif // Scroller2DPlugin_H
