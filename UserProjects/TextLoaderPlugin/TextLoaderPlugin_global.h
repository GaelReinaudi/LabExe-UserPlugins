#ifndef TextLoaderPlugin_GLOBAL_H
#define TextLoaderPlugin_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef TextLoaderPlugin_LIB
# define TextLoaderPlugin_EXPORT Q_DECL_EXPORT
#else
# define TextLoaderPlugin_EXPORT Q_DECL_IMPORT
#endif

#endif // TextLoaderPlugin_GLOBAL_H
