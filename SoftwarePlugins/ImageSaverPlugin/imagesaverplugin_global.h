#ifndef IMAGESAVERPLUGIN_GLOBAL_H
#define IMAGESAVERPLUGIN_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef IMAGESAVERPLUGIN_LIB
# define IMAGESAVERPLUGIN_EXPORT Q_DECL_EXPORT
#else
# define IMAGESAVERPLUGIN_EXPORT Q_DECL_IMPORT
#endif

#endif // IMAGESAVERPLUGIN_GLOBAL_H
