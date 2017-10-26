#include "serialcomportplugin.h"

Q_EXPORT_PLUGIN2(MenloDDS120Plugin, GMenloDDS120Plugin)

GMenloDDS120Plugin::GMenloDDS120Plugin(QObject *parent)
	: GDevicePlugin(parent)
{
	setObjectName("Novatech 425A");
}

GMenloDDS120Plugin::~GMenloDDS120Plugin()
{

}
