#ifndef GCLASSPLUGINDEVICETEMPLATE_H
#define GCLASSPLUGINDEVICETEMPLATE_H

#include "device.h"
#include "param.h"

/////////////////////////////////////////////////////////////////////
//! \brief The GClassPluginDeviceTemplate class implements a GProgDevice.
/*!
This prog device allows you to ..............
*/
class GClassPluginDeviceTemplate : public GProgDevice
{
	Q_OBJECT

public:
	GClassPluginDeviceTemplate(QObject *parent, QString uniqueIdentifierName = "");
	~GClassPluginDeviceTemplate();

protected:
	//! Re-implemented
	void PopulateDeviceWidget(GDeviceWidget* theDeviceWidget);

private:
	//! an example of a parameter
	GParamInt m_MyNumber;
	//! another, which we will declare read-only, i.e. the user cannot modify it directly
	GParamDouble m_MyDouble;

};

#endif // GCLASSPLUGINDEVICETEMPLATE_H
