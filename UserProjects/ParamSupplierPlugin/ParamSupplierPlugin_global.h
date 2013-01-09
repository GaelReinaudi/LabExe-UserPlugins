#ifndef ParamSupplierPlugin_GLOBAL_H
#define ParamSupplierPlugin_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef ParamSupplierPlugin_LIB
# define ParamSupplierPlugin_EXPORT Q_DECL_EXPORT
#else
# define ParamSupplierPlugin_EXPORT Q_DECL_IMPORT
#endif

#endif // ParamSupplierPlugin_GLOBAL_H
