#ifndef GSERIALPORTCONTROLLERWIDGET_H
#define GSERIALPORTCONTROLLERWIDGET_H

#include "GNovatech425A.h"
#include <QWidget>
#include "hled.h"

namespace Ui {class GNovatech425AWidget;};

class GNovatech425AWidget : public QWidget
{
	Q_OBJECT

public:
	GNovatech425AWidget(GNovatech425A* pTheController, QWidget *parent = 0);
	~GNovatech425AWidget();
	

protected slots:
	void ConnectedLED();
	void ConnectedClockLED();
	void DisconnectedLED();
	void DisconnectedClockLED();
	void WidgetClearCursor();


private:
	Ui::GNovatech425AWidget *ui;
	//Ui2::PortSettingsWidget *ui2;
	//! Pointer to the actual controller this widget will be interacting with.
	//friend class GNovatech425A;
	GNovatech425A* m_pController;
	//GNovatech425A* m_pController2;
	HLed *led;
	HLed *ledClock;

	friend class GNovatech425A;
};

#endif // GSERIALPORTCONTROLLERWIDGET_H
