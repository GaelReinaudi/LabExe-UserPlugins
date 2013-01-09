#include "StepperPlugin.h"

Q_EXPORT_PLUGIN2(GStepperPlugin, GStepperPlugin)

GStepperPlugin::GStepperPlugin(QObject *parent)
	: GDevicePlugin(parent)
{
}

GStepperPlugin::~GStepperPlugin()
{

}
