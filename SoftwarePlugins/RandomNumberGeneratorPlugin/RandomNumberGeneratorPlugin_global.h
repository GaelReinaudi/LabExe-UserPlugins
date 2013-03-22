#ifndef RandomNumberGeneratorPlugin_GLOBAL_H
#define RandomNumberGeneratorPlugin_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef RandomNumberGeneratorPlugin_LIB
# define RandomNumberGeneratorPlugin_EXPORT Q_DECL_EXPORT
#else
# define RandomNumberGeneratorPlugin_EXPORT Q_DECL_IMPORT
#endif

#endif // RandomNumberGeneratorPlugin_GLOBAL_H
