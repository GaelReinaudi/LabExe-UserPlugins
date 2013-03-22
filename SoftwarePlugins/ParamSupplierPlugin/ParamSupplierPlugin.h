#ifndef ParamSupplierPlugin_H
#define ParamSupplierPlugin_H
#include "ParamSupplierPlugin_global.h"
#include "device.h"

#include "GParamSupplier.h"

/////////////////////////////////////////////////////////////////////
//! \brief The GParamSupplierPlugin class implements the GDevicePlugin that provides a low pass filtered for a parameter.
/*!
This plugin allows you to define an input parameter by drag-and-dropping it in a param-bucket. 
When the input is updated, the average over the past n values is calculated and sent to 
an output param-bucket. n is defined by a spin-box.
If there are not yet n values in the past history of the parameter, the average is made on all existing data. 
The reset button clears the history of the parameter.
*/
class ParamSupplierPlugin_EXPORT GParamSupplierPlugin : public GDevicePlugin
{
	Q_OBJECT
	Q_INTERFACES(GDevicePlugin)
	G_REGISTER_PLUGIN_PROG_DEVICE(GParamSupplier)

public:
	GParamSupplierPlugin(QObject *parent = 0);
	~GParamSupplierPlugin();

private:

};

#endif // ParamSupplierPlugin_H
