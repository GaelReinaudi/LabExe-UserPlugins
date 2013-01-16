#ifndef GPHIDGETMANAGERWIDGET_H
#define GPHIDGETMANAGERWIDGET_H

#include "Device/GDeviceWidget.h"

class GPhidgetManager;

class GPhidgetManagerWidget : public GDeviceWidget
{
	Q_OBJECT

public:
	GPhidgetManagerWidget(GPhidgetManager* pOfWhichDevice, QWidget *parent);
	~GPhidgetManagerWidget();

protected slots:
	void UpdateSubDevicesWidgetList();

private:
	QList<GDevice*> m_ListDev;
	
};

#endif // GPHIDGETMANAGERWIDGET_H
