#include "ParamSupplierPlugin.h"

Q_EXPORT_PLUGIN2(GParamSupplierPlugin, GParamSupplierPlugin)

GParamSupplierPlugin::GParamSupplierPlugin(QObject *parent)
	: GDevicePlugin(parent)
{
}

GParamSupplierPlugin::~GParamSupplierPlugin()
{

}
