#ifndef Novatech425APLUGIN_GLOBAL_H
#define Novatech425APLUGIN_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef Novatech425APLUGIN_LIB
# define Novatech425APLUGIN_EXPORT Q_DECL_EXPORT
#else
# define Novatech425APLUGIN_EXPORT Q_DECL_IMPORT
#endif

#endif // Novatech425APLUGIN_GLOBAL_H
