#include "GInternetBrowser.h"
#include "googlechat.h"

GInternetBrowser::GInternetBrowser(QObject *parent, QString uniqueIdentifierName /* = "" */)
	: GProgDevice(parent, uniqueIdentifierName)
{
}

GInternetBrowser::~GInternetBrowser()
{

}

void GInternetBrowser::PopulateDeviceWidget(GDeviceWidget* theDeviceWidget )
{
	// a form layout
 	QBoxLayout* pLay = new QVBoxLayout();
	theDeviceWidget->AddSubLayout(pLay);
	pLay->addWidget(new GoogleChat());
}
