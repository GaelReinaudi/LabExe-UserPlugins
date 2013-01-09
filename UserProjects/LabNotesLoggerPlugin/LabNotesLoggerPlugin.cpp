#include "LabNotesLoggerPlugin.h"

Q_EXPORT_PLUGIN2(GLabNotesLoggerPlugin, GLabNotesLoggerPlugin)

GLabNotesLoggerPlugin::GLabNotesLoggerPlugin(QObject *parent)
	: GDevicePlugin(parent)
{
}

GLabNotesLoggerPlugin::~GLabNotesLoggerPlugin()
{

}
