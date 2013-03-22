#ifndef PARAMPLOTTERPLUGIN_H
#define PARAMPLOTTERPLUGIN_H
#include "paramplotterplugin_global.h"
#include "device.h"

#include "GParamPlotter.h"

/////////////////////////////////////////////////////////////////////
//! \brief The GParamPlotterPlugin class implements the GDevicePlugin.
/*!
This plugin will register the GParamPlotter class in the device manager for plotting numerical parameters (GParamNum).
*/
class PARAMPLOTTERPLUGIN_EXPORT GParamPlotterPlugin : public GDevicePlugin
{
	Q_OBJECT
	Q_INTERFACES(GDevicePlugin)
	G_REGISTER_PLUGIN_PROG_DEVICE(GParamPlotter)

public:
	GParamPlotterPlugin(QObject *parent = 0);
	~GParamPlotterPlugin();

private:

};

#endif // PARAMPLOTTERPLUGIN_H
