#include "paramplotterplugin.h"

GParamPlotterPlugin::GParamPlotterPlugin(QObject *parent)
	: GDevicePlugin(parent)
{
	setObjectName("Param plotter");
}

GParamPlotterPlugin::~GParamPlotterPlugin()
{

}
