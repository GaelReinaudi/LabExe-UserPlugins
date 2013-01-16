#ifndef BetterAbsorptionImagePlugin_H
#define BetterAbsorptionImagePlugin_H
#include "BetterAbsorptionImagePlugin_global.h"
#include "device.h"

#include "GBetterAbsorptionImage.h"

/////////////////////////////////////////////////////////////////////
//! \brief The GBetterAbsorptionImagePlugin class implements the GDevicePlugin.
/*!
This plugin allows you to intercept images coming from a camera and compute the absorption image.
*/
class IMAGEABSORPTIONPLUGIN_EXPORT GBetterAbsorptionImagePlugin : public GDevicePlugin
{
	Q_OBJECT
	Q_INTERFACES(GDevicePlugin)
	G_REGISTER_PLUGIN_PROG_DEVICE(GBetterAbsorptionImage)

public:
	GBetterAbsorptionImagePlugin(QObject *parent = 0);
	~GBetterAbsorptionImagePlugin();

private:

};

#endif // BetterAbsorptionImagePlugin_H
