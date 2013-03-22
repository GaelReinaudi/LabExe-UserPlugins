#ifndef ImageAbsorptionPlugin_GLOBAL_H
#define ImageAbsorptionPlugin_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef IMAGEABSORPTIONPLUGIN_LIB
# define IMAGEABSORPTIONPLUGIN_EXPORT Q_DECL_EXPORT
#else
# define IMAGEABSORPTIONPLUGIN_EXPORT Q_DECL_IMPORT
#endif

#endif // ImageAbsorptionPlugin_GLOBAL_H
