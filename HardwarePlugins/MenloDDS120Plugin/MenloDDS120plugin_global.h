#ifndef MenloDDS120PLUGIN_GLOBAL_H
#define MenloDDS120PLUGIN_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef MenloDDS120PLUGIN_LIB
# define MenloDDS120PLUGIN_EXPORT Q_DECL_EXPORT
#else
# define MenloDDS120PLUGIN_EXPORT Q_DECL_IMPORT
#endif

#endif // MenloDDS120PLUGIN_GLOBAL_H
