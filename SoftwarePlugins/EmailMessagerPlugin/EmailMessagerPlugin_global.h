#ifndef EmailMessagerPlugin_GLOBAL_H
#define EmailMessagerPlugin_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef EmailMessagerPlugin_LIB
# define EmailMessagerPlugin_EXPORT Q_DECL_EXPORT
#else
# define EmailMessagerPlugin_EXPORT Q_DECL_IMPORT
#endif

#endif // EmailMessagerPlugin_GLOBAL_H
