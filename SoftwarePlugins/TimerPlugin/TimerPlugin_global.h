#ifndef TimerPlugin_GLOBAL_H
#define TimerPlugin_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef TimerPlugin_LIB
# define TimerPlugin_EXPORT Q_DECL_EXPORT
#else
# define TimerPlugin_EXPORT Q_DECL_IMPORT
#endif

#endif // TimerPlugin_GLOBAL_H
