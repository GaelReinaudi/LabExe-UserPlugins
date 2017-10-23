#ifndef SRSControllerPlugin_H
#define SRSControllerPlugin_H
#include "SRSControllerPlugin_global.h"
#include "device.h"

#include "GSRSController.h"

/////////////////////////////////////////////////////////////////////
//! \brief The GSRSControllerPlugin class implements the GDevicePlugin that provides a low pass filtered for a parameter.
/*!
This plugin allows you to define an input parameter by drag-and-dropping it in a param-bucket. 
When the input is updated, the average over the past n values is calculated and sent to 
an output param-bucket. n is defined by a spin-box.
If there are not yet n values in the past history of the parameter, the average is made on all existing data. 
The reset button clears the history of the parameter.
*/
class SRSControllerPlugin_EXPORT GSRSControllerPlugin : public GDevicePlugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Gael.GDevicePlugin/2.0")
	Q_INTERFACES(GDevicePlugin)
	G_REGISTER_PLUGIN_PROG_DEVICE(GSRSController)

public:
	GSRSControllerPlugin(QObject *parent = 0);
	~GSRSControllerPlugin();

private:

};

#endif // SRSControllerPlugin_H
