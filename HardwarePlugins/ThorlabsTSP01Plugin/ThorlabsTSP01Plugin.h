#ifndef ThorlabsTSP01Plugin_H
#define ThorlabsTSP01Plugin_H
#include "ThorlabsTSP01Plugin_global.h"
#include "device.h"

#include "GThorlabsTSP01.h"

/////////////////////////////////////////////////////////////////////
//! \brief The GThorlabsTSP01Plugin class implements the GDevicePlugin that provides a low pass filtered for a parameter.
/*!
This plugin allows you to define an input parameter by drag-and-dropping it in a param-bucket. 
When the input is updated, the average over the past n values is calculated and sent to 
an output param-bucket. n is defined by a spin-box.
If there are not yet n values in the past history of the parameter, the average is made on all existing data. 
The reset button clears the history of the parameter.
*/
class ThorlabsTSP01Plugin_EXPORT GThorlabsTSP01Plugin : public GDevicePlugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Gael.GDevicePlugin/2.0")
	Q_INTERFACES(GDevicePlugin)
	G_REGISTER_PLUGIN_HARD_DEVICE(GThorlabsTSP01, "Thorlabs TSP01");

public:
	GThorlabsTSP01Plugin(QObject *parent = 0);
	~GThorlabsTSP01Plugin();

private:

};

#endif // ThorlabsTSP01Plugin_H
