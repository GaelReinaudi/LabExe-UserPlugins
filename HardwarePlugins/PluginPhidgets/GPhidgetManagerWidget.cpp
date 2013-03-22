#include "GPhidgetManagerWidget.h"
#include "GPhidgetManager.h"

GPhidgetManagerWidget::GPhidgetManagerWidget(GPhidgetManager* pOfWhichDevice, QWidget *parent)
	: GDeviceWidget(pOfWhichDevice, parent)
{
	QBoxLayout* DeviceLayout = new QBoxLayout(QBoxLayout::TopToBottom);
	setLayout(DeviceLayout);
	DeviceLayout->setContentsMargins(0, 0, 0, 0);
}

GPhidgetManagerWidget::~GPhidgetManagerWidget()
{

}

void GPhidgetManagerWidget::UpdateSubDevicesWidgetList()
{
	GPhidgetManager* pPhidMan = qobject_cast<GPhidgetManager*>(Device());
	QLayout *pLayout = layout();
	if(!pPhidMan || !pLayout)
		return;
	QList<GDevice*> oldList = m_ListDev;
	m_ListDev = pPhidMan->m_SerialPhidgetModules.values();
	// make a list of new items in the m_ListDev
	QList<GDevice*> newDevicesInList = m_ListDev;
	foreach(GDevice* pDev, m_ListDev)
		if(oldList.contains(pDev))
			newDevicesInList.removeOne(pDev);
	// make a list of items that are gone from the m_ListDev
	QList<GDevice*> goneDevicesInList = oldList;
	foreach(GDevice* pDev, oldList)
		if(m_ListDev.contains(pDev))
			goneDevicesInList.removeOne(pDev);

	// lets delete the gone's and create the new's
	foreach(GDevice* pDev, goneDevicesInList) {
		for (int i = 0; i < pLayout->count(); ++i) {
			GDeviceWidget* pWid = qobject_cast<GDeviceWidget*>(pLayout->itemAt(i)->widget());
			if(pWid && goneDevicesInList.contains(pWid->Device())) {
				pLayout->removeWidget(pWid);
				delete pWid;
			}
		}
	}
	foreach(GDevice* pDev, newDevicesInList) {
		GDeviceWidget* subDevWidget = pDev->ProvideNewDeviceGroupBox(this);
		pLayout->addWidget(subDevWidget);
	}
}