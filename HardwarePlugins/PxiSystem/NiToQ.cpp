#include "NiToQ.h"

QString NiToQString(CNiString strrr) {
	QString newstr(strrr);
	return newstr;
}

QStringList NiToQString(CNiStringVector list) {
	QStringList newlist;
	for(unsigned long i = 0; i < list.GetSize(); i++)
		newlist.append(NiToQString(list[i]));
	return newlist;
}

CNiDAQmxDevice PxiDaqDevice( QString &NiDeviceName )
{
	return CNiDAQmxSystem::LoadDevice(NiDeviceName.toAscii());
}