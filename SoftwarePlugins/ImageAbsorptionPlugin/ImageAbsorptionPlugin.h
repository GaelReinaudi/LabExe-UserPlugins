#ifndef ImageAbsorptionPlugin_H
#define ImageAbsorptionPlugin_H
#include "ImageAbsorptionPlugin_global.h"
#include "device.h"

#include "GAbsorptionImageProcessor.h"

/////////////////////////////////////////////////////////////////////
//! \brief The GImageAbsorptionPlugin class implements the GDevicePlugin.
/*!
This plugin allows you to intercept images coming from a camera and compute the absorption image.
*/
class IMAGEABSORPTIONPLUGIN_EXPORT GImageAbsorptionPlugin : public GDevicePlugin
{
	Q_OBJECT
	Q_PLUGIN_METADATA(IID "Gael.GDevicePlugin/2.0")
	Q_INTERFACES(GDevicePlugin)
	G_REGISTER_PLUGIN_PROG_DEVICE(GAbsorptionImageProcessor)

public:
	GImageAbsorptionPlugin(QObject *parent = 0);
	~GImageAbsorptionPlugin();

private:

};

#endif // ImageAbsorptionPlugin_H
