#ifndef LockingSlapperPlugin_H
#define LockingSlapperPlugin_H
#include "LockingSlapperPlugin_global.h"
#include "device.h"

#include "GLockingSlapper.h"

/////////////////////////////////////////////////////////////////////
//! \brief The GLockingSlapperPlugin class implements the GDevicePlugin that provides a low pass filtered for a parameter.
/*!
This plugin allows you to define an input parameter by drag-and-dropping it in a param-bucket. 
When the input is updated, the average over the past n values is calculated and sent to 
an output param-bucket. n is defined by a spin-box.
If there are not yet n values in the past history of the parameter, the average is made on all existing data. 
The reset button clears the history of the parameter.
*/
class LockingSlapperPlugin_EXPORT GLockingSlapperPlugin : public GDevicePlugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Gael.GDevicePlugin/2.0")
	Q_INTERFACES(GDevicePlugin)
	G_REGISTER_PLUGIN_PROG_DEVICE(GLockingSlapper)

public:
	GLockingSlapperPlugin(QObject *parent = 0);
	~GLockingSlapperPlugin();

private:

};

#endif // LockingSlapperPlugin_H
