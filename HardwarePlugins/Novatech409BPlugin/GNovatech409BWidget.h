#ifndef GSERIALPORTCONTROLLERWIDGET_H
#define GSERIALPORTCONTROLLERWIDGET_H

#include "GNovatech409B.h"
#include <QWidget>
#include "hled.h"

namespace Ui {class GNovatech409BWidget;};

class GNovatech409BWidget : public QWidget
{
	Q_OBJECT

public:
	GNovatech409BWidget(GNovatech409B* pTheController, QWidget *parent = 0);
	~GNovatech409BWidget();
	

protected slots:
	void ConnectedLED();
	void DisconnectedLED();
	void WidgetClearCursor();


private:
	Ui::GNovatech409BWidget *ui;
	//Ui2::PortSettingsWidget *ui2;
	//! Pointer to the actual controller this widget will be interacting with.
	//friend class GNovatech409B;
	GNovatech409B* m_pController;
	//GNovatech409B* m_pController2;
	HLed *led;

	friend class GNovatech409B;
};

#endif // GSERIALPORTCONTROLLERWIDGET_H
