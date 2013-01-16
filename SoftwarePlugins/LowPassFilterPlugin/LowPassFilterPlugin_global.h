#ifndef LowPassFilterPlugin_GLOBAL_H
#define LowPassFilterPlugin_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef LowPassFilterPlugin_LIB
# define LowPassFilterPlugin_EXPORT Q_DECL_EXPORT
#else
# define LowPassFilterPlugin_EXPORT Q_DECL_IMPORT
#endif

#endif // LowPassFilterPlugin_GLOBAL_H
