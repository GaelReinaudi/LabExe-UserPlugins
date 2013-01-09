#ifndef RollingStatsPlugin_GLOBAL_H
#define RollingStatsPlugin_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef RollingStatsPlugin_LIB
# define RollingStatsPlugin_EXPORT Q_DECL_EXPORT
#else
# define RollingStatsPlugin_EXPORT Q_DECL_IMPORT
#endif

#endif // RollingStatsPlugin_GLOBAL_H
