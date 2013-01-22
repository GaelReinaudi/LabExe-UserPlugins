#ifndef PlotXYPlugin_H
#define PlotXYPlugin_H
#include "PlotXYPlugin_global.h"
#include "device.h"

#include "GPlotXY.h"

/////////////////////////////////////////////////////////////////////
//! \brief The GPlotXYPlugin class implements the GDevicePlugin that provides a low pass filtered for a parameter.
/*!
This plugin allows you to define an input parameter by drag-and-dropping it in a param-bucket. 
When the input is updated, the average over the past n values is calculated and sent to 
an output param-bucket. n is defined by a spin-box.
If there are not yet n values in the past history of the parameter, the average is made on all existing data. 
The reset button clears the history of the parameter.
*/
class PlotXYPlugin_EXPORT GPlotXYPlugin : public GDevicePlugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Gael.GDevicePlugin/2.0")
	Q_INTERFACES(GDevicePlugin)
	G_REGISTER_PLUGIN_PROG_DEVICE(GPlotXY)

public:
	GPlotXYPlugin(QObject *parent = 0);
	~GPlotXYPlugin();

private:

};

#endif // PlotXYPlugin_H
