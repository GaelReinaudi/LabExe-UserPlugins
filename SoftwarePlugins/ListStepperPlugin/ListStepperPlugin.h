#ifndef LISTSTEPPERPLUGIN_H
#define LISTSTEPPERPLUGIN_H

#include "ListStepperPlugin_global.h"
#include "device.h"
#include "GListStepper.h"

/////////////////////////////////////////////////////////////////////
//! \brief The GListStepperPlugin class implements a plugin that provides a stepper through a list of user-defined values.
/*!
This plugin allows you to define a list of values to step through in a text box.
When the input bucket receives a trigger, it outputs the next value in the list.
The list of values is specified in a text box and can be comma, space, or newline separated.
The reset button restarts from the beginning of the list.
*/
class GListStepperPlugin : public GDevicePlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "Gael.GDevicePlugin/2.0")
    Q_INTERFACES(GDevicePlugin)
    G_REGISTER_PLUGIN_PROG_DEVICE(GListStepper)

public:
    GListStepperPlugin(QObject *parent = 0);
    ~GListStepperPlugin();

private:

};

#endif // LISTSTEPPERPLUGIN_H 