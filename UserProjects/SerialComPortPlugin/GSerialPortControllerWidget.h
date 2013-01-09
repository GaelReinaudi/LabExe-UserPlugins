#ifndef GSERIALPORTCONTROLLERWIDGET_H
#define GSERIALPORTCONTROLLERWIDGET_H

#include "GSerialPortController.h"
#include <QWidget>
#include "hled.h"

namespace Ui {class GSerialPortControllerWidget;};

class GSerialPortControllerWidget : public QWidget
{
	Q_OBJECT

public:
	GSerialPortControllerWidget(GSerialPortController* pTheController, QWidget *parent = 0);
	~GSerialPortControllerWidget();
	

protected slots:
	void ConnectedLED();
	void DisconnectedLED();
	void WidgetClearCursor();


private:
	Ui::GSerialPortControllerWidget *ui;
	//Ui2::PortSettingsWidget *ui2;
	//! Pointer to the actual controller this widget will be interacting with.
	//friend class GSerialPortController;
	GSerialPortController* m_pController;
	//GSerialPortController* m_pController2;
	HLed *led;

	friend class GSerialPortController;
};

#endif // GSERIALPORTCONTROLLERWIDGET_H
