#ifndef Novatech409B_GLOBAL_H
#define Novatech409B_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef Novatech409BPLUGIN_LIB
# define Novatech409BPLUGIN_EXPORT Q_DECL_EXPORT
#else
# define Novatech409BPLUGIN_EXPORT Q_DECL_IMPORT
#endif

#endif // Novatech409B_GLOBAL_H
