#include "numericalexpressionplugin.h"

Q_EXPORT_PLUGIN2(NumericalExpressionPlugin, GNumericalExpressionPlugin)

GNumericalExpressionPlugin::GNumericalExpressionPlugin(QObject *parent)
	: GDevicePlugin(parent)
{
	setObjectName("Numerical expression");
}

GNumericalExpressionPlugin::~GNumericalExpressionPlugin()
{

}
