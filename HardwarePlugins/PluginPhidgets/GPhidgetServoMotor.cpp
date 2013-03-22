#include "GPhidgetServoMotor.h"
#include "GPhidgetAdvancedServoModule.h"
#include "GPhidgetServoMotorWidget.h"

G_REGISTER_HARD_DEVICE_CLASS(GPhidgetServoMotor)

GPhidgetServoMotor::GPhidgetServoMotor(QString uniqueIdentifierName, QObject *parent)
	: GServoMotor(uniqueIdentifierName, parent)
	, m_VelocityLimit("Limit speed", this)
	, m_AccelerationLimit("Acceleration", this)
	, m_VelocityWhenLastChecked(0.0)
{
	m_TargetPos.SetHardLimits(-90, 90);
	m_TargetPos.SetTypicalStep(5.0);

	ReName(DefaultShortName());
	emit IsAblenessMayHaveChanged(IsAble());

	connect(&m_VelocityLimit, SIGNAL(ValueUpdated(double)), this, SLOT(SetMaxVelocity(double)));
	connect(&m_AccelerationLimit, SIGNAL(ValueUpdated(double)), this, SLOT(SetMaxAcceleration(double)));
}

GPhidgetServoMotor::~GPhidgetServoMotor()
{

}

void GPhidgetServoMotor::PopulateDeviceWidget(GDeviceWidget* theDeviceWidget )
{
	theDeviceWidget->DontDisplayTitle();
	QBoxLayout* pLay = new QHBoxLayout();
	pLay->setContentsMargins(0, 0, 0, 0);
	theDeviceWidget->AddSubLayout(pLay);

	QDoubleSpinBox* pSpinBox = m_TargetPos.ProvideNewParamSpinBox(theDeviceWidget);
	QLabel* nameLabel = m_TargetPos.ProvideNewLabel(theDeviceWidget);
	pLay->addWidget(nameLabel);
	pLay->addWidget(pSpinBox);
	
	QAbstractButton* pMovingBox = new QCheckBox("moving", theDeviceWidget);
	connect(this, SIGNAL(MovingOrStopped(bool)), pMovingBox, SLOT(setChecked(bool)), Qt::QueuedConnection);
	pLay->addWidget(pMovingBox);
}

QString GPhidgetServoMotor::DefaultShortName() const
{
	QString thename = Name();
	if(!ParentModule())
		return thename;
	int serialN = ParentModule()->SerialNumber();
	return QString("P%1-S%2").arg(serialN).arg(IndexMotor());// + thename.split(PHIDGET_SERVO_NUMBER_SEPARATOR).last();
}

GPhidgetAdvancedServoModule* GPhidgetServoMotor::ParentModule() const
{
	return qobject_cast<GPhidgetAdvancedServoModule*>(parent());
}

void GPhidgetServoMotor::MoveAbsolute( double newPos)
{
	if(!IsAble()) {
		return emit FinishedMoveToTargetPosition(false);
	}
	if(gEqual(newPos, ParentModule()->GetTargetPosition(IndexMotor())))
		return emit FinishedMoveToTargetPosition(true);

	// first Engage(), then SetTargetPosition() so that the servo doesn't snap to position when it is re-engaged (after it was disengaged).
	// Also, it prevents to emit a PositionChanged handler when re-engaging (ie after it was disengaged).
	Engage(true);
	ParentModule()->SetTargetPosition(IndexMotor(), newPos);
}

void GPhidgetServoMotor::SetMaxVelocity( double maxVel )
{
	if(!IsAble()) {
		return;
	}
	ParentModule()->SetVelocityLimit(IndexMotor(), maxVel);
}

void GPhidgetServoMotor::SetMaxAcceleration( double maxAcc )
{
	if(!IsAble()) {
		return;
	}
	ParentModule()->SetAccelerationLimit(IndexMotor(), maxAcc);
}

void GPhidgetServoMotor::Engage( bool doEngage )
{	
	// commented some checking to gain time since it looks this function is called from other functions where the checking is done!
	// 	if(!IsAble())
	// 		return;
	ParentModule()->SetEngage(IndexMotor(), doEngage);
}

void GPhidgetServoMotor::Disengage()
{
 	if(!IsAble())
 		return;
	ParentModule()->SetEngage(IndexMotor(), false);
}

int GPhidgetServoMotor::IndexMotor() const
{	
	// commented some checking to gain time since it looks this function is called from other functions where the checking is done!
	//if(!IsAble())
	//	return -1;
	// from parent module subdevices list BUT PROBLEM when the servo was just being created and is not in the list yet
	if(false) {
		GPhidgetServoMotor* pDev = const_cast<GPhidgetServoMotor*>(this);
		return ParentModule()->SubDevices().indexOf(pDev);
	}
	// from the device name
	if(true)
		return ParentModule()->GetIndexServoFromPhidgetServoIdentifier(UniqueSystemID());
}

bool GPhidgetServoMotor::IsAble() const
{
	if(ParentModule())
		if(ParentModule()->IsAble())
			return true;
	return false;
}

void GPhidgetServoMotor::ModuleTriggeredPositionChanged( double thePos, double theVel )
{
	bool stopped = (theVel == 0.0 && m_VelocityWhenLastChecked != 0.0);
	bool started = (theVel != 0.0 && m_VelocityWhenLastChecked == 0.0);
	m_VelocityWhenLastChecked = theVel;

	emit MovingOrStopped(theVel != 0.0);
	emit PositionChanged(thePos, theVel);
	if(theVel == 0.0)
		if(ParentModule()->IsStopped(IndexMotor()))
			emit FinishedMoveToTargetPosition(true);
}

QWidget* GPhidgetServoMotor::ProvideNewExtraSettingsWidget( QWidget* parentWidget )
{
	return new GPhidgetServoMotorWidget(this, parentWidget);
}
