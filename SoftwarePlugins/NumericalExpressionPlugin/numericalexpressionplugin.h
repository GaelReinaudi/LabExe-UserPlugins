#ifndef NUMERICALEXPRESSIONPLUGIN_H
#define NUMERICALEXPRESSIONPLUGIN_H
#include "numericalexpressionplugin_global.h"
#include "device.h"

#include "GNumericalExpression.h"

/////////////////////////////////////////////////////////////////////
//! \brief The GNumericalExpressionPlugin class implements a generic way of computing expression from parameters.
/*!
This plugin will register the GNumericalExpression class in the device manager for providing a gui allowing expression evaluation.
*/
class NUMERICALEXPRESSIONPLUGIN_EXPORT GNumericalExpressionPlugin : public GDevicePlugin
{
	Q_OBJECT
	Q_INTERFACES(GDevicePlugin)
	G_REGISTER_PLUGIN_PROG_DEVICE(GNumericalExpression)

public:
	GNumericalExpressionPlugin(QObject *parent = 0);
	~GNumericalExpressionPlugin();

private:

};

#endif // NUMERICALEXPRESSIONPLUGIN_H
