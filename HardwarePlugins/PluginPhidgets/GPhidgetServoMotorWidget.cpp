#include "GPhidgetServoMotorWidget.h"

GPhidgetServoMotorWidget::GPhidgetServoMotorWidget(GPhidgetServoMotor* pServo, QWidget *parent)
	: QWidget(parent)
	, m_pServo(pServo)
{
	setupUi(this);
	pVelAccLayout->addRow(m_pServo->m_VelocityLimit.ProvideNewLabel(this), m_pServo->m_VelocityLimit.ProvideNewParamSpinBox(this));
	pVelAccLayout->addRow(m_pServo->m_AccelerationLimit.ProvideNewLabel(this), m_pServo->m_AccelerationLimit.ProvideNewParamSpinBox(this));
	pDisengageLayout->addRow(m_pServo->m_DisengageAfterMove.ProvideNewLabel(this), m_pServo->m_DisengageAfterMove.ProvideNewParamCheckBox(this, ""));
	pDisengageLayout->addRow(m_pServo->m_DelayToDisEngageAfterMove.ProvideNewLabel(this), m_pServo->m_DelayToDisEngageAfterMove.ProvideNewParamWidget(this));
}

GPhidgetServoMotorWidget::~GPhidgetServoMotorWidget()
{

}
