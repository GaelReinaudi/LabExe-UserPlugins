#ifndef PORTSETTINGSWIDGETNovatech425A_H
#define PORTSETTINGSWIDGETNovatech425A_H

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
	friend class GNovatech425A;
};

#endif // PORTSETTINGSWIDGETNovatech425A_H
