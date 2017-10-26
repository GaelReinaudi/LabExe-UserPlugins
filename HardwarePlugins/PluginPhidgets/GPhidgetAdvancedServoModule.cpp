#include "GPhidgetAdvancedServoModule.h"
#include "GPhidgetManager.h"
#include "GPhidgetServoMotor.h"
#include "GPhidget21.h"

G_REGISTER_HARD_DEVICE_CLASS(GPhidgetAdvancedServoModule)

// uncomment this to get some debugging code for the servos
//#define DEBUG_SERVO_PHIDGET

#ifdef DEBUG_SERVO_PHIDGET
QListWidget* m_pDebugListView;
QMutex m_pDebugMutex;
#endif

#define G_PHIDGET_SERVO_NEUTRAL_ANGLE (90.0)

/////////////////////////////////////////////////////////////////////
/*! \relates GPhidgetAdvancedServoModule
\brief GServoModulePositionChangeHandler() is function called when a phidget servo module considers a servo moved. 
The phidget API knows that it has to call this function because I call this Phidget-API function:
\code PhidgetRCServo_setOnPositionChangeHandler(m_ThePhidgetAdvancedServo, GServoModulePositionChangeHandler, this); \endcode
\param:  PhidgetRCServoHandle ADVSERVO : the phidget-API needed handle to a servo module
\param:  void * pPhiMod : a user pointer that I happened to be the pointer to the GPhidgetAdvancedServoModule object that fired the event.
*////////////////////////////////////////////////////////////////////
int __stdcall GServoModulePositionChangeHandler(PhidgetRCServoHandle ADVSERVO, void *pPhiMod, int Index, double Value)
{
	double vel = 0.0;
	PhidgetRCServo_getVelocity(ADVSERVO, Index, &vel);
	GPhidgetAdvancedServoModule* pPhidgetModule = (GPhidgetAdvancedServoModule*)pPhiMod;
	if(pPhidgetModule)
		pPhidgetModule->TriggeredPositionChanged(Index, Value, vel);
#ifdef DEBUG_SERVO_PHIDGET
	if(Index == 1 && vel == 0.0)
		return 0;
#endif

	return 0;
}

/////////////////////////////////////////////////////////////////////
/*! \relates GPhidgetAdvancedServoModule
\brief GServoModuleVelocityChangeHandler() is function called when a phidget servo module considers a servo changed velocity. 
The phidget API knows that it has to call this function because I call this Phidget-API function:
\code PhidgetRCServo_setOnVelocityChangeHandler(m_ThePhidgetAdvancedServo, GServoModuleVelocityChangeHandler, this); \endcode
\param:  PhidgetRCServoHandle ADVSERVO : the phidget-API needed handle to a servo module
\param:  void * pPhiMod : a user pointer that I happened to be the pointer to the GPhidgetAdvancedServoModule object that fired the event.
*////////////////////////////////////////////////////////////////////
int __stdcall GServoModuleVelocityChangeHandler(PhidgetRCServoHandle ADVSERVO, void *pPhiMod, int Index, double Value)
{
	GPhidgetAdvancedServoModule* pPhidgetModule = (GPhidgetAdvancedServoModule*)pPhiMod;
	if(pPhidgetModule)
		pPhidgetModule->TriggeredVelocityChanged(Index, Value);
	return 0;
}

/////////////////////////////////////////////////////////////////////
/*! \relates GPhidgetAdvancedServoModule
\brief unused for now
*////////////////////////////////////////////////////////////////////
int __stdcall GServoModuleCurrentChangeHandler(PhidgetRCServoHandle ADVSERVO, void *pPhiMod, int Index, double Value)
{
// 	unused for now
 	return 0;
}

GPhidgetAdvancedServoModule::GPhidgetAdvancedServoModule(QString uniqueIdentifierName, QObject *parent)
	: GPhidgetModule(uniqueIdentifierName, parent)
	, m_ThePhidgetAdvancedServo(0)
	, m_NumberMotors(0)
{
	m_SerialNumber = GPhidgetManager::GetSerialFromPhidgetIdentifier(UniqueSystemID());
	if(!m_SerialNumber)
		return;

#ifdef DEBUG_SERVO_PHIDGET
	m_pDebugListView = new QListWidget(0);
	m_pDebugListView->show();
#endif

	//create the advanced servo object
	PhidgetRCServo_create(&m_ThePhidgetAdvancedServo);
}

GPhidgetAdvancedServoModule::~GPhidgetAdvancedServoModule()
{
	if(!m_ThePhidgetAdvancedServo)
		return;
	//... terminate the program so we will close the phidget and delete the object we created
	Phidget_close(ThePhidgetHandle());
	Phidget_delete(&ThePhidgetHandle());
	//all done, exit
}

void GPhidgetAdvancedServoModule::DelayedPhidgetInitialization()
{
	//Registers a callback that will run when the motor position is changed.
	//Requires the handle for the phidget, the function that will be called, and an arbitrary pointer that will be supplied to the callback function (may be NULL).
	PhidgetRCServo_setOnPositionChangeHandler(m_ThePhidgetAdvancedServo, GServoModulePositionChangeHandler, this);
	PhidgetRCServo_setOnVelocityChangeHandler(m_ThePhidgetAdvancedServo, GServoModuleVelocityChangeHandler, this);
	//	PhidgetRCServo_setOnCurrentChangeHandler(m_ThePhidgetAdvancedServo, GServoModuleCurrentChangeHandler, this);

	ConfigureWhenPluggedIn();
}

void GPhidgetAdvancedServoModule::ConfigureWhenPluggedIn()
{
	// get the number of motors
	PhidgetRCServo_getMotorCount(m_ThePhidgetAdvancedServo, &m_NumberMotors);
	// create the servos object
	CreateSubDevicesServos();

	for(int indexMotor = 0; indexMotor < m_NumberMotors; indexMotor++) {
		SetEngage(indexMotor, false);
		PhidgetRCServo_setServoType(m_ThePhidgetAdvancedServo, indexMotor, PHIDGET_SERVO_HITEC_HS322HD);
		GPhidgetServoMotor* pSer = Servo(indexMotor);
		if(pSer) {
			SetTargetPosition(indexMotor, pSer->TargetPosition());
		}

		// some values
		double minPos = 0.0; double maxPos = 0.0; double accMin = 0.0; double accMax = 0.0; double velMin = 0.0; double velMax = 0.0; double acc = 0.0; double vel = 0.0; double velLim = 0.0;
		// test to make the velocity small to debug some stuffs
		PhidgetRCServo_getMinPosition(m_ThePhidgetAdvancedServo, indexMotor, &minPos);
		PhidgetRCServo_getMaxPosition(m_ThePhidgetAdvancedServo, indexMotor, &maxPos);
		PhidgetRCServo_getMinAcceleration(m_ThePhidgetAdvancedServo, indexMotor, &accMin);
		PhidgetRCServo_getMaxAcceleration(m_ThePhidgetAdvancedServo, indexMotor, &accMax);
		PhidgetRCServo_getVelocityLimit(m_ThePhidgetAdvancedServo, indexMotor, &velMax);
		PhidgetRCServo_getVelocityLimit(m_ThePhidgetAdvancedServo, indexMotor, &velLim);
		PhidgetRCServo_getAcceleration(m_ThePhidgetAdvancedServo, indexMotor, &acc);

		PhidgetRCServo_setSpeedRampingOn(m_ThePhidgetAdvancedServo, indexMotor, 1);

		if(pSer->m_VelocityLimit.DoubleValue() == 0.0)
			pSer->m_VelocityLimit = velMax;
		if(pSer->m_AccelerationLimit.DoubleValue() == 0.0)
			pSer->m_AccelerationLimit = accMax;

		pSer->m_VelocityLimit.SetHardLimits(velMin, velMax);
		pSer->m_AccelerationLimit.SetHardLimits(accMin, accMax);
		pSer->m_VelocityLimit.SetTypicalStep(10);
		pSer->m_AccelerationLimit.SetTypicalStep(100);
		pSer->m_VelocityLimit.SetDisplayDecimals(1);
		pSer->m_AccelerationLimit.SetDisplayDecimals(1);
	}
	emit IsAblenessMayHaveChanged(IsAble());
}

void GPhidgetAdvancedServoModule::CreateSubDevicesServos()
{
	if(!IsAble())
		return;
	m_ListServos.clear();
	for(int indexServo = 0; indexServo < m_NumberMotors; indexServo++) {
		QString nameServo = CreateUniqueServoIdentifier(indexServo);
		// if it already exist, lets not make it again.
		GDevice* pServo = GetDeviceFromDeviceManager(nameServo);
		// but let's make sure or set the correct parent module (in case it was created	at startup, without the module parent created...)
		if(pServo && !pServo->parent())
			pServo->setParent(this);
		if(!pServo)
			pServo = new GPhidgetServoMotor(nameServo, this);
		m_ListServos.append(pServo);
		disconnect(this, SIGNAL(IsAblenessMayHaveChanged(bool)), pServo, SIGNAL(IsAblenessMayHaveChanged(bool)));
		connect(this, SIGNAL(IsAblenessMayHaveChanged(bool)), pServo, SIGNAL(IsAblenessMayHaveChanged(bool)), Qt::QueuedConnection);
		//TODO what to do for servos not in TheBenchDevices?		
		// should they move to ? no!?
		disconnect(this, SIGNAL(IsAblenessMayHaveChanged(bool)), pServo, SLOT(Engage(bool)));
		connect(this, SIGNAL(IsAblenessMayHaveChanged(bool)), pServo, SLOT(Engage(bool)), Qt::QueuedConnection);
	}
}

void GPhidgetAdvancedServoModule::PopulateDeviceWidget(GDeviceWidget* theDeviceWidget )
{
	QWidget* pWid = new QWidget(theDeviceWidget);
	theDeviceWidget->layout()->addWidget(pWid);
	// layout
	QBoxLayout* servosLayout = new QVBoxLayout(pWid);
	servosLayout->setContentsMargins(1, 1, 1, 1);

	for(int indexServo = 0; indexServo < m_NumberMotors; indexServo++) {
		GPhidgetServoMotor* pServo = Servo(indexServo);
		if(!pServo)
			continue;
// 		servosLayout->addWidget(pServo->ProvideNewExtraSettingsWidget(theDeviceWidget));
	}
	servosLayout->addStretch();

return;
// 
// 
// 	// a combo to drag and drop the subdevices in the lab
// 	QComboBox* pComboServos = new QComboBox(theDeviceWidget);
// 	pComboServos->view()->setDragDropMode(QAbstractItemView::DragOnly);
// 	pComboServos->setModel(new GDeviceListModel(pComboServos));
// 	// Let's populate the combo with names and the pointer to the corresponding GDevice's. (We use QVariant for that).
// 	foreach(GDevice* pDev, m_ListServos) {
// 		pComboServos->addItem(pDev->Name(), QVariant::fromValue(pDev->UniqueSystemID()));
// 	}
// 	servosLayout->addWidget(pComboServos);
}

bool GPhidgetAdvancedServoModule::IsAble() const
{
	if(m_IsAttached)
		if(m_ThePhidgetAdvancedServo)
			if(m_SerialNumber)
				if(ParentManager())
					return true;
	return false;
}

QString GPhidgetAdvancedServoModule::CreateUniqueServoIdentifier(int indexServo) const {
	return UniqueSystemID() + QString("%1%2").arg(PHIDGET_SERVO_NUMBER_SEPARATOR).arg(indexServo);
}

int GPhidgetAdvancedServoModule::GetIndexServoFromPhidgetServoIdentifier( QString strUniqueID )
{
	bool conversionOK = false;
	int indexServo = strUniqueID.split(PHIDGET_SERVO_NUMBER_SEPARATOR).last().toInt(&conversionOK);
	if(conversionOK)
		return indexServo;
	else
		return -1;
}

GPhidgetServoMotor* GPhidgetAdvancedServoModule::Servo( int indexServo ) const
{
	if(indexServo < SubDevices().count())
		return qobject_cast<GPhidgetServoMotor*>(SubDevices().at(indexServo));
	return 0;
}

double GPhidgetAdvancedServoModule::GetTargetPosition( int indexServo ) const
{	// commented some checking to gain time since it looks this function is called from other functions where the checking is done!
	//if(!IsAble())
	//	return 0.0;
	double theAngleFromNeutral = 0.0;
	int result = PhidgetRCServo_getPosition (m_ThePhidgetAdvancedServo, indexServo, &theAngleFromNeutral);
	return theAngleFromNeutral - G_PHIDGET_SERVO_NEUTRAL_ANGLE;
}

void GPhidgetAdvancedServoModule::SetTargetPosition( int indexServo, double newAngle )
{	// commented some checking to gain time since it looks this function is called from other functions where the checking is done!
	//if(!IsAble())
	//	return;
	double newAngleFromNeutral = newAngle + G_PHIDGET_SERVO_NEUTRAL_ANGLE;
	int result = PhidgetRCServo_setPosition (m_ThePhidgetAdvancedServo, indexServo, newAngleFromNeutral);
	result = 0;
}

void GPhidgetAdvancedServoModule::SetEngage( int indexServo, bool doEngage )
{	// commented some checking to gain time since it looks this function is called from other functions where the checking is done!
	//if(!IsAble())
	//	return;
	PhidgetRCServo_setEngaged(m_ThePhidgetAdvancedServo, indexServo, doEngage ? 1 : 0);
}

bool GPhidgetAdvancedServoModule::IsStopped(int indexServo)
{	// commented some checking to gain time since it looks this function is called from other functions where the checking is done!
	//if(!IsAble())
	//	return true;
	int isSt;
	PhidgetRCServo_getStopped(m_ThePhidgetAdvancedServo, indexServo, &isSt);
	return isSt != 0;
}

void GPhidgetAdvancedServoModule::TriggeredVelocityChanged( int indexServo, double theVel )
{
	GPhidgetServoMotor* pTheServo = Servo(indexServo);
}

void GPhidgetAdvancedServoModule::TriggeredPositionChanged( int indexServo, double thePos, double theVelo )
{
	double thePosFromNeutral = thePos - G_PHIDGET_SERVO_NEUTRAL_ANGLE;
	double theVelocity = theVelo;
	GPhidgetServoMotor* pTheServo = Servo(indexServo);
	if(pTheServo)
		pTheServo->ModuleTriggeredPositionChanged(thePosFromNeutral, theVelocity);
#ifdef DEBUG_SERVO_PHIDGET
	m_pDebugMutex.lock();
	m_pDebugListView->addItem(QString("Servo %1 - Pos = %2 - Vel = %3").arg(indexServo).arg(thePosFromNeutral).arg(theVelo));
//	m_pDebugListView->scrollToBottom();
//	m_pDebugListView->insertItem(0, QString("Servo %1 - Pos = %2 - Vel = %3").arg(indexServo).arg(thePosFromNeutral).arg(theVelo));
	m_pDebugMutex.unlock();
#endif // DEBUG_SERVO_PHIDGET
}

void GPhidgetAdvancedServoModule::SetVelocityLimit( int indexServo, double newVelMax )
{
	if(!IsAble())
		return;
	int result = PhidgetRCServo_setVelocityLimit(m_ThePhidgetAdvancedServo, indexServo, newVelMax);
}

void GPhidgetAdvancedServoModule::SetAccelerationLimit( int indexServo, double newAccMax )
{
	if(!IsAble())
		return;
	int result = PhidgetRCServo_setAcceleration(m_ThePhidgetAdvancedServo, indexServo, newAccMax);
}
