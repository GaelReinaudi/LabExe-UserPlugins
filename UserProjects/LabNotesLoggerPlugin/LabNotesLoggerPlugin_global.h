#ifndef LabNotesLoggerPlugin_GLOBAL_H
#define LabNotesLoggerPlugin_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef LabNotesLoggerPlugin_LIB
# define LabNotesLoggerPlugin_EXPORT Q_DECL_EXPORT
#else
# define LabNotesLoggerPlugin_EXPORT Q_DECL_IMPORT
#endif

#endif // LabNotesLoggerPlugin_GLOBAL_H
