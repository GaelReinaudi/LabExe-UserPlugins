#include "Plot1DPlugin.h"

Q_EXPORT_PLUGIN2(GPlot1DPlugin, GPlot1DPlugin)

GPlot1DPlugin::GPlot1DPlugin(QObject *parent)
	: GDevicePlugin(parent)
{
}

GPlot1DPlugin::~GPlot1DPlugin()
{

}
