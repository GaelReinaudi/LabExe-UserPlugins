#ifndef PORTSETTINGSWIDGETNovatech409B_H
#define PORTSETTINGSWIDGETNovatech409B_H

#include <QWidget>
#include "ui_PortSettingsWidget.h"

class PortSettingsWidget : public QWidget
{
	Q_OBJECT

public:
	PortSettingsWidget(QWidget *parent = 0);
	~PortSettingsWidget();

private:
	Ui::PortSettingsWidget ui;
	friend class GNovatech409B;
};

#endif // PORTSETTINGSWIDGETNovatech409B_H
