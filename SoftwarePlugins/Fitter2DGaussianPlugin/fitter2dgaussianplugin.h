#ifndef FITTER2DGAUSSIANPLUGIN_H
#define FITTER2DGAUSSIANPLUGIN_H
#include "fitter2dgaussianplugin_global.h"
#include "device.h"

#include "GImage2DGaussFitter.h"

/////////////////////////////////////////////////////////////////////
//! \brief The GFitter2DGaussianPlugin class implements the GDevicePlugin.
/*!
This plugin will register the GImage2DGaussFitter in the device manager for computing the fitting of a gaussian shape on an image.
*/
class FITTER2DGAUSSIANPLUGIN_EXPORT GFitter2DGaussianPlugin : public GDevicePlugin
{
	Q_OBJECT
	Q_INTERFACES(GDevicePlugin)
	G_REGISTER_PLUGIN_PROG_DEVICE(GImage2DGaussFitter)

public:
	GFitter2DGaussianPlugin(QObject *parent = 0);
	~GFitter2DGaussianPlugin();

private:

};

#endif // FITTER2DGAUSSIANPLUGIN_H
