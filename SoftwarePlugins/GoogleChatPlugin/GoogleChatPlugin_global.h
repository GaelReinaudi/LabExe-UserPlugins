#ifndef GoogleChatPlugin_GLOBAL_H
#define GoogleChatPlugin_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef GoogleChatPlugin_LIB
# define GoogleChatPlugin_EXPORT Q_DECL_EXPORT
#else
# define GoogleChatPlugin_EXPORT Q_DECL_IMPORT
#endif

#endif // GoogleChatPlugin_GLOBAL_H
