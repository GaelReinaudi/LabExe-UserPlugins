#ifndef TextLoaderPlugin_H
#define TextLoaderPlugin_H
#include "TextLoaderPlugin_global.h"
#include "device.h"

#include "GTextLoader.h"

/////////////////////////////////////////////////////////////////////
//! \brief The GTextLoaderPlugin class implements the GDevicePlugin that provides a low pass filtered for a parameter.
/*!
This plugin allows you to define an input parameter by drag-and-dropping it in a param-bucket. 
When the input is updated, the average over the past n values is calculated and sent to 
an output param-bucket. n is defined by a spin-box.
If there are not yet n values in the past history of the parameter, the average is made on all existing data. 
The reset button clears the history of the parameter.
*/
class TextLoaderPlugin_EXPORT GTextLoaderPlugin : public GDevicePlugin
{
	Q_OBJECT
	Q_INTERFACES(GDevicePlugin)
	G_REGISTER_PLUGIN_PROG_DEVICE(GTextLoader)

public:
	GTextLoaderPlugin(QObject *parent = 0);
	~GTextLoaderPlugin();

private:

};

#endif // TextLoaderPlugin_H
