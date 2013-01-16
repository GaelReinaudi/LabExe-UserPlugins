#include "fitter2dgaussianplugin.h"

Q_EXPORT_PLUGIN2(Fitter2DGaussianPlugin, GFitter2DGaussianPlugin)

GFitter2DGaussianPlugin::GFitter2DGaussianPlugin(QObject *parent)
	: GDevicePlugin(parent)
{
	setObjectName("2D gaussian fitter");
}

GFitter2DGaussianPlugin::~GFitter2DGaussianPlugin()
{

}
