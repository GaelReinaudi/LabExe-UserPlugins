#ifndef Plot1DPlugin_GLOBAL_H
#define Plot1DPlugin_GLOBAL_H

#include <QtGlobal>

#ifdef Plot1DPlugin_LIB
# define Plot1DPlugin_EXPORT Q_DECL_EXPORT
#else
# define Plot1DPlugin_EXPORT Q_DECL_IMPORT
#endif

#endif // Plot1DPlugin_GLOBAL_H
