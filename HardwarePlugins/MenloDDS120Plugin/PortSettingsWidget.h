#ifndef PORTSETTINGSWIDGET_H
#define PORTSETTINGSWIDGET_H

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

#endif // PORTSETTINGSWIDGET_H
