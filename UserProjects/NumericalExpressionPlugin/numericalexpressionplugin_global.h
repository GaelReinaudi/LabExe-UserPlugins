#ifndef NUMERICALEXPRESSIONPLUGIN_GLOBAL_H
#define NUMERICALEXPRESSIONPLUGIN_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef NUMERICALEXPRESSIONPLUGIN_LIB
# define NUMERICALEXPRESSIONPLUGIN_EXPORT Q_DECL_EXPORT
#else
# define NUMERICALEXPRESSIONPLUGIN_EXPORT Q_DECL_IMPORT
#endif

#endif // NUMERICALEXPRESSIONPLUGIN_GLOBAL_H
