#ifndef PORTSETTINGSWIDGETMenloDDS120_H
#define PORTSETTINGSWIDGETMenloDDS120_H

#include <QWidget>
#include "ui_portsettingswidget.h"

class PortSettingsWidget : public QWidget
{
	Q_OBJECT

public:
	PortSettingsWidget(QWidget *parent = 0);
	~PortSettingsWidget();

private:
	Ui::PortSettingsWidget ui;
	friend class GMenloDDS120;
};

#endif // PORTSETTINGSWIDGETMenloDDS120_H
