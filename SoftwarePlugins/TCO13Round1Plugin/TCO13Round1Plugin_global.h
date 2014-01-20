#ifndef TCO13Round1Plugin_GLOBAL_H
#define TCO13Round1Plugin_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef TCO13Round1Plugin_LIB
# define TCO13Round1Plugin_EXPORT Q_DECL_EXPORT
#else
# define TCO13Round1Plugin_EXPORT Q_DECL_IMPORT
#endif

#endif // TCO13Round1Plugin_GLOBAL_H
