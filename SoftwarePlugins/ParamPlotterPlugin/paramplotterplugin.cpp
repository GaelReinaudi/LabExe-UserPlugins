#include "paramplotterplugin.h"

Q_EXPORT_PLUGIN2(ParamPlotterPlugin, GParamPlotterPlugin)

GParamPlotterPlugin::GParamPlotterPlugin(QObject *parent)
	: GDevicePlugin(parent)
{
	setObjectName("Param plotter");
}

GParamPlotterPlugin::~GParamPlotterPlugin()
{

}
