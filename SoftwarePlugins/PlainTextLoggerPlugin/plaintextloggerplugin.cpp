#include "plaintextloggerplugin.h"

Q_EXPORT_PLUGIN2(PlainTextLoggerPlugin, GPlainTextLoggerPlugin)

GPlainTextLoggerPlugin::GPlainTextLoggerPlugin(QObject *parent)
	: GDevicePlugin(parent)
{
	setObjectName("Plain text logger");
}

GPlainTextLoggerPlugin::~GPlainTextLoggerPlugin()
{

}
