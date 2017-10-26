#ifndef ThorlabsTSP01Plugin_GLOBAL_H
#define ThorlabsTSP01Plugin_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef ThorlabsTSP01Plugin_LIB
# define ThorlabsTSP01Plugin_EXPORT Q_DECL_EXPORT
#else
# define ThorlabsTSP01Plugin_EXPORT Q_DECL_IMPORT
#endif

#endif // ThorlabsTSP01Plugin_GLOBAL_H
