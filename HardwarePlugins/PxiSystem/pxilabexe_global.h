#ifndef PXILABEXE_GLOBAL_H
#define PXILABEXE_GLOBAL_H

#include <qglobal.h>

#ifdef PXILABEXE_LIB
# define PXILABEXE_EXPORT Q_DECL_EXPORT
#else
# define PXILABEXE_EXPORT Q_DECL_IMPORT
#endif

#endif // PXILABEXE_GLOBAL_H
