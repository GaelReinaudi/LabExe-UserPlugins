#ifndef NITOQ_H
#define NITOQ_H

#include <QtGui>
#include "stdafx.h"

QString NiToQString(CNiString strrr);
QStringList NiToQString(CNiStringVector list);

CNiDAQmxDevice PxiDaqDevice( QString &NiDeviceName );

#endif // NITOQ_H
