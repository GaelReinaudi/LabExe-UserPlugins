#ifndef GSERIALPORTCONTROLLERWIDGET_H
#define GSERIALPORTCONTROLLERWIDGET_H

#include "GMenloDDS120.h"
#include <QWidget>
#include "hled.h"

namespace Ui {class GMenloDDS120Widget;};

class GMenloDDS120Widget : public QWidget
{
	Q_OBJECT

public:
	GMenloDDS120Widget(GMenloDDS120* pTheController, QWidget *parent = 0);
	~GMenloDDS120Widget();
	

protected slots:
	void ConnectedLED();
	//void ConnectedClockLED();
	void DisconnectedLED();
	//void DisconnectedClockLED();
	void WidgetClearCursor();


private:
	Ui::GMenloDDS120Widget *ui;
	//Ui2::PortSettingsWidget *ui2;
	//! Pointer to the actual controller this widget will be interacting with.
	//friend class GMenloDDS120;
	GMenloDDS120* m_pController;
	//GMenloDDS120* m_pController2;
	HLed *led;
	//HLed *ledClock;

	friend class GMenloDDS120;
};

#endif // GSERIALPORTCONTROLLERWIDGET_H
