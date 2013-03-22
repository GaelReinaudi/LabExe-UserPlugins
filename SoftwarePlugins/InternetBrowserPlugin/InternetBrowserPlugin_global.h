#ifndef InternetBrowserPlugin_GLOBAL_H
#define InternetBrowserPlugin_GLOBAL_H

#include <QtCore/qglobal.h>

#ifdef InternetBrowserPlugin_LIB
# define InternetBrowserPlugin_EXPORT Q_DECL_EXPORT
#else
# define InternetBrowserPlugin_EXPORT Q_DECL_IMPORT
#endif

#endif // InternetBrowserPlugin_GLOBAL_H
