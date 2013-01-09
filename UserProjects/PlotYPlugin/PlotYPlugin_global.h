#ifndef PlotYPlugin_GLOBAL_H
#define PlotYPlugin_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef PlotYPlugin_LIB
# define PlotYPlugin_EXPORT Q_DECL_EXPORT
#else
# define PlotYPlugin_EXPORT Q_DECL_IMPORT
#endif

#endif // PlotYPlugin_GLOBAL_H
