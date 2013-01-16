#ifndef GPHIDGETSERVOMOTORWIDGET_H
#define GPHIDGETSERVOMOTORWIDGET_H

#include <QWidget>
#include "ui_GPhidgetServoMotorWidget.h"
#include "GPhidgetServoMotor.h"

class GPhidgetServoMotorWidget : public QWidget, public Ui::GPhidgetServoMotorWidget
{
	Q_OBJECT

public:
	GPhidgetServoMotorWidget(GPhidgetServoMotor* pServo, QWidget *parent = 0);
	~GPhidgetServoMotorWidget();

private:
	GPhidgetServoMotor* m_pServo;
};

#endif // GPHIDGETSERVOMOTORWIDGET_H
