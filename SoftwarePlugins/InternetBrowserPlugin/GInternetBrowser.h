#ifndef GInternetBrowser_H
#define GInternetBrowser_H

#include "device.h"
#include "param.h"

/////////////////////////////////////////////////////////////////////
//! \brief The GInternetBrowser class implements a GProgDevice.
/*!
This prog device allows you to go on the web..............
*/
class GInternetBrowser : public GProgDevice
{
	Q_OBJECT

public:
	GInternetBrowser(QObject *parent, QString uniqueIdentifierName = "");
	~GInternetBrowser();

protected:
	//! Re-implemented
	void PopulateDeviceWidget(GDeviceWidget* theDeviceWidget);

private:

};

#endif // GInternetBrowser_H
