#ifndef LISTSTEPPERPLUGIN_GLOBAL_H
#define LISTSTEPPERPLUGIN_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(ListStepperPlugin_LIB)
#  define ListeStepperPlugin_LIB Q_DECL_EXPORT
#else
#  define ListeStepperPlugin_LIB Q_DECL_IMPORT
#endif

#endif // LISTSTEPPERPLUGIN_GLOBAL_H 
