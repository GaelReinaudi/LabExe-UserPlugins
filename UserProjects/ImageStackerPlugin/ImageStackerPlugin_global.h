#ifndef ImageStackerPlugin_GLOBAL_H
#define ImageStackerPlugin_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef ImageStackerPlugin_LIB
# define ImageStackerPlugin_EXPORT Q_DECL_EXPORT
#else
# define ImageStackerPlugin_EXPORT Q_DECL_IMPORT
#endif

#endif // ImageStackerPlugin_GLOBAL_H
