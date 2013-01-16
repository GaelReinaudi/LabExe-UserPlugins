#ifndef BetterAbsorptionImagePlugin_GLOBAL_H
#define BetterAbsorptionImagePlugin_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef IMAGEABSORPTIONPLUGIN_LIB
# define IMAGEABSORPTIONPLUGIN_EXPORT Q_DECL_EXPORT
#else
# define IMAGEABSORPTIONPLUGIN_EXPORT Q_DECL_IMPORT
#endif

#endif // BetterAbsorptionImagePlugin_GLOBAL_H
