#include "plaintextloggerplugin.h"

GPlainTextLoggerPlugin::GPlainTextLoggerPlugin(QObject *parent)
	: GDevicePlugin(parent)
{
	setObjectName("Plain text logger");
}

GPlainTextLoggerPlugin::~GPlainTextLoggerPlugin()
{

}
