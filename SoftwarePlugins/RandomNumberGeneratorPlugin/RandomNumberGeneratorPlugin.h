#ifndef RandomNumberGeneratorPlugin_H
#define RandomNumberGeneratorPlugin_H
#include "RandomNumberGeneratorPlugin_global.h"
#include "device.h"

#include "GRandomNumberGenerator.h"

/////////////////////////////////////////////////////////////////////
//! \brief The GRandomNumberGeneratorPlugin class implements the GDevicePlugin.
/*!
This plugin allows you to ..............
*/
class RandomNumberGeneratorPlugin_EXPORT GRandomNumberGeneratorPlugin : public GDevicePlugin
{
	Q_OBJECT
	Q_INTERFACES(GDevicePlugin)
	G_REGISTER_PLUGIN_PROG_DEVICE(GRandomNumberGenerator)

public:
	GRandomNumberGeneratorPlugin(QObject *parent = 0);
	~GRandomNumberGeneratorPlugin();

private:

};

#endif // RandomNumberGeneratorPlugin_H
