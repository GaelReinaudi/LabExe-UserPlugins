#ifndef Plot1DPlugin_H
#define Plot1DPlugin_H
#include "Plot1DPlugin_global.h"
#include "device.h"

#include "GPlot1D.h"

/////////////////////////////////////////////////////////////////////
//! \brief The GPlot1DPlugin class implements the GDevicePlugin that provides a low pass filtered for a parameter.
/*!
This plugin allows you to define an input parameter by drag-and-dropping it in a param-bucket. 
When the input is updated, the average over the past n values is calculated and sent to 
an output param-bucket. n is defined by a spin-box.
If there are not yet n values in the past history of the parameter, the average is made on all existing data. 
The reset button clears the history of the parameter.
*/
class Plot1DPlugin_EXPORT GPlot1DPlugin : public GDevicePlugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Gael.GDevicePlugin/2.0")
	Q_INTERFACES(GDevicePlugin)
	G_REGISTER_PLUGIN_PROG_DEVICE(GPlot1D)

public:
	GPlot1DPlugin(QObject *parent = 0);
	~GPlot1DPlugin();

private:

};

#endif // Plot1DPlugin_H
