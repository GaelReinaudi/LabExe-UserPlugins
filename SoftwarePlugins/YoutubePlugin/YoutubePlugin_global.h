#ifndef YoutubePlugin_GLOBAL_H
#define YoutubePlugin_GLOBAL_H

#include <Qglobal.h>

#ifdef YoutubePlugin_LIB
# define YoutubePlugin_EXPORT Q_DECL_EXPORT
#else
# define YoutubePlugin_EXPORT Q_DECL_IMPORT
#endif

#endif // YoutubePlugin_GLOBAL_H
