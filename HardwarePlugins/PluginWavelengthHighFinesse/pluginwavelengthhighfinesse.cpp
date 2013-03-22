#include "pluginwavelengthhighfinesse.h"

Q_EXPORT_PLUGIN2(GPluginWavelengthHighFinesse, GPluginWavelengthHighFinesse)

GPluginWavelengthHighFinesse::GPluginWavelengthHighFinesse(QObject *parent /*= 0*/)
	: GDevicePlugin(parent)
{
	setObjectName("Wavelength-meter HighFinesse");
}

GPluginWavelengthHighFinesse::~GPluginWavelengthHighFinesse()
{

}
