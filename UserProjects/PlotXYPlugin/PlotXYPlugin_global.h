#ifndef PlotXYPlugin_GLOBAL_H
#define PlotXYPlugin_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef PlotXYPlugin_LIB
# define PlotXYPlugin_EXPORT Q_DECL_EXPORT
#else
# define PlotXYPlugin_EXPORT Q_DECL_IMPORT
#endif

#endif // PlotXYPlugin_GLOBAL_H
