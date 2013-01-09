#ifndef SRSControllerPlugin_GLOBAL_H
#define SRSControllerPlugin_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef SRSControllerPlugin_LIB
# define SRSControllerPlugin_EXPORT Q_DECL_EXPORT
#else
# define SRSControllerPlugin_EXPORT Q_DECL_IMPORT
#endif

#endif // SRSControllerPlugin_GLOBAL_H
