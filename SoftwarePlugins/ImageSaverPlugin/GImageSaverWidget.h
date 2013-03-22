#ifndef GIMAGESAVERWIDGET_H
#define GIMAGESAVERWIDGET_H

#include <QWidget>
#include "ui_GImageSaverWidget.h"

class GImageSaver;

class GImageSaverWidget : public QWidget, public Ui::GImageSaverWidget
{
	Q_OBJECT

public:
	GImageSaverWidget(GImageSaver* pImageSaver, QWidget *parent = 0);
	~GImageSaverWidget();
};

#endif // GIMAGESAVERWIDGET_H
