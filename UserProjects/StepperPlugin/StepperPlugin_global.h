#ifndef StepperPlugin_GLOBAL_H
#define StepperPlugin_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef StepperPlugin_LIB
# define StepperPlugin_EXPORT Q_DECL_EXPORT
#else
# define StepperPlugin_EXPORT Q_DECL_IMPORT
#endif

#endif // StepperPlugin_GLOBAL_H
