#ifndef PLAINTEXTLOGGERPLUGIN_H
#define PLAINTEXTLOGGERPLUGIN_H
#include "plaintextloggerplugin_global.h"
#include "device.h"

#include "GPlainTextLogger.h"

/////////////////////////////////////////////////////////////////////
//! \brief The GPlainTextLoggerPlugin class implements the GDevicePlugin.
/*!
This plugin ...
*/
class PLAINTEXTLOGGERPLUGIN_EXPORT GPlainTextLoggerPlugin : public GDevicePlugin
{
	Q_OBJECT
	Q_INTERFACES(GDevicePlugin)
	G_REGISTER_PLUGIN_PROG_DEVICE(GPlainTextLogger)

public:
	GPlainTextLoggerPlugin(QObject *parent = 0);
	~GPlainTextLoggerPlugin();

private:

};

#endif // PLAINTEXTLOGGERPLUGIN_H
