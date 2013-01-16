#ifndef LINEARCOMBINATIONPLUGIN_H
#define LINEARCOMBINATIONPLUGIN_H
#include "linearcombinationplugin_global.h"
#include "device.h"

#include "GLinearCombination.h"

/////////////////////////////////////////////////////////////////////
//! \brief The GLinearCombinationPlugin class implements a plugin for computing linear combinations of parameters.
/*!
This plugin will register the GLinearCombination class in the device manager for providing a gui allowing linear combinations.
*/
class LINEARCOMBINATIONPLUGIN_EXPORT GLinearCombinationPlugin : public GDevicePlugin
{
	Q_OBJECT
	Q_INTERFACES(GDevicePlugin)
	G_REGISTER_PLUGIN_PROG_DEVICE(GLinearCombination)

public:
	GLinearCombinationPlugin(QObject *parent = 0);
	~GLinearCombinationPlugin();

private:

};

#endif // LINEARCOMBINATIONPLUGIN_H
