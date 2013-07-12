#ifndef Scroller2DPlugin_GLOBAL_H
#define Scroller2DPlugin_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef Scroller2DPlugin_LIB
# define Scroller2DPlugin_EXPORT Q_DECL_EXPORT
#else
# define Scroller2DPlugin_EXPORT Q_DECL_IMPORT
#endif

#endif // Scroller2DPlugin_GLOBAL_H
