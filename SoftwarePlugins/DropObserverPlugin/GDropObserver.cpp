#include "GDropObserver.h"
#include "GDropAttributeWidget.h"

GDropObserver::GDropObserver(QObject *parent, QString uniqueIdentifierName /* = "" */)
	: GProgDevice(parent, uniqueIdentifierName)
	, m_MyNumber("iterations", this)
	, m_MyDouble("speed", this, GParam::ReadOnly)
{
	// put initialization code here
}

GDropObserver::~GDropObserver()
{

}

void GDropObserver::PopulateDeviceWidget(GDeviceWidget* theDeviceWidget )
{
	QWidget* pWid = new GDropAttributeWidget(theDeviceWidget);

	QVBoxLayout* pLay = new QVBoxLayout();
	theDeviceWidget->AddSubLayout(pLay);
	pLay->addWidget(pWid);
}
