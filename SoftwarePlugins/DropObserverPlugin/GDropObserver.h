#ifndef GDropObserver_H
#define GDropObserver_H

#include "device.h"
#include "param.h"

/////////////////////////////////////////////////////////////////////
//! \brief The GDropObserver class implements a GProgDevice.
/*!
This prog device allows you to ..............
*/
class GDropObserver : public GProgDevice
{
	Q_OBJECT

public:
	GDropObserver(QObject *parent, QString uniqueIdentifierName = "");
	~GDropObserver();

protected:
	//! Re-implemented
	void PopulateDeviceWidget(GDeviceWidget* theDeviceWidget);

private:
	//! an example of a parameter
	GParamInt m_MyNumber;
	//! another, which we will declare read-only, i.e. the user cannot modify it directly
	GParamDouble m_MyDouble;

};

#endif // GDropObserver_H
