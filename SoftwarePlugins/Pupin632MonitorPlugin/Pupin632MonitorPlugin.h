#ifndef Pupin632MonitorPlugin_H
#define Pupin632MonitorPlugin_H
#include "Pupin632MonitorPlugin_global.h"
#include "device.h"

#include "GPupin632Monitor.h"

/////////////////////////////////////////////////////////////////////
//! \brief The GPupin632MonitorPlugin class implements the GDevicePlugin that provides a low pass filtered for a parameter.
/*!
This plugin allows you to define an input parameter by drag-and-dropping it in a param-bucket. 
When the input is updated, the average over the past n values is calculated and sent to 
an output param-bucket. n is defined by a spin-box.
If there are not yet n values in the past history of the parameter, the average is made on all existing data. 
The reset button clears the history of the parameter.
*/
class Pupin632MonitorPlugin_EXPORT GPupin632MonitorPlugin : public GDevicePlugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Gael.GDevicePlugin/2.0")
	Q_INTERFACES(GDevicePlugin)
	G_REGISTER_PLUGIN_PROG_DEVICE(GPupin632Monitor)

public:
	GPupin632MonitorPlugin(QObject *parent = 0);
	~GPupin632MonitorPlugin();

private:

};

#endif // Pupin632MonitorPlugin_H
