#ifndef MenloDDS120PLUGIN_H
#define MenloDDS120PLUGIN_H
#include "MenloDDS120plugin_global.h"
#include "device.h"

#include "GMenloDDS120.h"

/////////////////////////////////////////////////////////////////////
//! \brief The GMenloDDS120Plugin class implements the GDevicePlugin.
/*!
This plugin allows you to control the serial port
*/
class MenloDDS120PLUGIN_EXPORT GMenloDDS120Plugin : public GDevicePlugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Gael.GDevicePlugin/2.0")
	Q_INTERFACES(GDevicePlugin)
	G_REGISTER_PLUGIN_HARD_DEVICE(GMenloDDS120,  "Menlo DDS120")

public:
	GMenloDDS120Plugin(QObject *parent = 0);
	~GMenloDDS120Plugin();

private:

};

#endif // MenloDDS120PLUGIN_H
