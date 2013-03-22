#ifndef LockingSlapperPlugin_GLOBAL_H
#define LockingSlapperPlugin_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef LockingSlapperPlugin_LIB
# define LockingSlapperPlugin_EXPORT Q_DECL_EXPORT
#else
# define LockingSlapperPlugin_EXPORT Q_DECL_IMPORT
#endif

#endif // LockingSlapperPlugin_GLOBAL_H
