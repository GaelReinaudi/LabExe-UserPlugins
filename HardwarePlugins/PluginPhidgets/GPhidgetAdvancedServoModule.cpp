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
\code CPhidgetAdvancedServo_set_OnPositionChange_Handler(m_TheCPhidgetAdvancedServo, GServoModulePositionChangeHandler, this); \endcode
\param:  CPhidgetAdvancedServoHandle ADVSERVO : the phidget-API needed handle to a servo module
\param:  void * pPhiMod : a user pointer that I happened to be the pointer to the GPhidgetAdvancedServoModule object that fired the event.
*////////////////////////////////////////////////////////////////////
int __stdcall GServoModulePositionChangeHandler(CPhidgetAdvancedServoHandle ADVSERVO, void *pPhiMod, int Index, double Value)
{
	double vel = 0.0;
	CPhidgetAdvancedServo_getVelocity(ADVSERVO, Index, &vel);
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
\code CPhidgetAdvancedServo_set_OnVelocityChange_Handler(m_TheCPhidgetAdvancedServo, GServoModuleVelocityChangeHandler, this); \endcode
\param:  CPhidgetAdvancedServoHandle ADVSERVO : the phidget-API needed handle to a servo module
\param:  void * pPhiMod : a user pointer that I happened to be the pointer to the GPhidgetAdvancedServoModule object that fired the event.
*////////////////////////////////////////////////////////////////////
int __stdcall GServoModuleVelocityChangeHandler(CPhidgetAdvancedServoHandle ADVSERVO, void *pPhiMod, int Index, double Value)
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
int __stdcall GServoModuleCurrentChangeHandler(CPhidgetAdvancedServoHandle ADVSERVO, void *pPhiMod, int Index, double Value)
{
// 	unused for now
 	return 0;
}

GPhidgetAdvancedServoModule::GPhidgetAdvancedServoModule(QString uniqueIdentifierName, QObject *parent)
	: GPhidgetModule(uniqueIdentifierName, parent)
	, m_TheCPhidgetAdvancedServo(0)
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
	CPhidgetAdvancedServo_create(&m_TheCPhidgetAdvancedServo);
}

GPhidgetAdvancedServoModule::~GPhidgetAdvancedServoModule()
{
	if(!m_TheCPhidgetAdvancedServo)
		return;
	//... terminate the program so we will close the phidget and delete the object we created
	CPhidget_close(TheCPhidgetHandle());
	CPhidget_delete(TheCPhidgetHandle());
	//all done, exit
}

void GPhidgetAdvancedServoModule::DelayedPhidgetInitialization()
{
	//Registers a callback that will run when the motor position is changed.
	//Requires the handle for the phidget, the function that will be called, and an arbitrary pointer that will be supplied to the callback function (may be NULL).
	CPhidgetAdvancedServo_set_OnPositionChange_Handler(m_TheCPhidgetAdvancedServo, GServoModulePositionChangeHandler, this);
	CPhidgetAdvancedServo_set_OnVelocityChange_Handler(m_TheCPhidgetAdvancedServo, GServoModuleVelocityChangeHandler, this);
	//	CPhidgetAdvancedServo_set_OnCurrentChange_Handler(m_TheCPhidgetAdvancedServo, GServoModuleCurrentChangeHandler, this);

	ConfigureWhenPluggedIn();
}

void GPhidgetAdvancedServoModule::ConfigureWhenPluggedIn()
{
	// get the number of motors
	CPhidgetAdvancedServo_getMotorCount(m_TheCPhidgetAdvancedServo, &m_NumberMotors);
	// create the servos object
	CreateSubDevicesServos();

	for(int indexMotor = 0; indexMotor < m_NumberMotors; indexMotor++) {
		SetEngage(indexMotor, false);
		CPhidgetAdvancedServo_setServoType(m_TheCPhidgetAdvancedServo, indexMotor, PHIDGET_SERVO_HITEC_HS322HD);
		GPhidgetServoMotor* pSer = Servo(indexMotor);
		if(pSer) {
			SetTargetPosition(indexMotor, pSer->TargetPosition());
		}

		// some values
		double minPos = 0.0; double maxPos = 0.0; double accMin = 0.0; double accMax = 0.0; double velMin = 0.0; double velMax = 0.0; double acc = 0.0; double vel = 0.0; double velLim = 0.0;
		// test to make the velocity small to debug some stuffs
		CPhidgetAdvancedServo_getPositionMin(m_TheCPhidgetAdvancedServo, indexMotor, &minPos);
		CPhidgetAdvancedServo_getPositionMax(m_TheCPhidgetAdvancedServo, indexMotor, &maxPos);
		CPhidgetAdvancedServo_getAccelerationMin(m_TheCPhidgetAdvancedServo, indexMotor, &accMin);
		CPhidgetAdvancedServo_getAccelerationMax(m_TheCPhidgetAdvancedServo, indexMotor, &accMax);
		CPhidgetAdvancedServo_getVelocityMin(m_TheCPhidgetAdvancedServo, indexMotor, &velMin);
		CPhidgetAdvancedServo_getVelocityMax(m_TheCPhidgetAdvancedServo, indexMotor, &velMax);
		CPhidgetAdvancedServo_getVelocityLimit(m_TheCPhidgetAdvancedServo, indexMotor, &velLim);
		CPhidgetAdvancedServo_getAcceleration(m_TheCPhidgetAdvancedServo, indexMotor, &acc);

		CPhidgetAdvancedServo_setSpeedRampingOn(m_TheCPhidgetAdvancedServo, indexMotor, 1);

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
		if(m_TheCPhidgetAdvancedServo)
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
	int result = CPhidgetAdvancedServo_getPosition (m_TheCPhidgetAdvancedServo, indexServo, &theAngleFromNeutral);
	return theAngleFromNeutral - G_PHIDGET_SERVO_NEUTRAL_ANGLE;
}

void GPhidgetAdvancedServoModule::SetTargetPosition( int indexServo, double newAngle )
{	// commented some checking to gain time since it looks this function is called from other functions where the checking is done!
	//if(!IsAble())
	//	return;
	double newAngleFromNeutral = newAngle + G_PHIDGET_SERVO_NEUTRAL_ANGLE;
	int result = CPhidgetAdvancedServo_setPosition (m_TheCPhidgetAdvancedServo, indexServo, newAngleFromNeutral);
	result = 0;
}

void GPhidgetAdvancedServoModule::SetEngage( int indexServo, bool doEngage )
{	// commented some checking to gain time since it looks this function is called from other functions where the checking is done!
	//if(!IsAble())
	//	return;
	CPhidgetAdvancedServo_setEngaged(m_TheCPhidgetAdvancedServo, indexServo, doEngage ? 1 : 0);
}

bool GPhidgetAdvancedServoModule::IsStopped(int indexServo)
{	// commented some checking to gain time since it looks this function is called from other functions where the checking is done!
	//if(!IsAble())
	//	return true;
	int isSt;
	CPhidgetAdvancedServo_getStopped(m_TheCPhidgetAdvancedServo, indexServo, &isSt);
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
	int result = CPhidgetAdvancedServo_setVelocityLimit(m_TheCPhidgetAdvancedServo, indexServo, newVelMax);
}

void GPhidgetAdvancedServoModule::SetAccelerationLimit( int indexServo, double newAccMax )
{
	if(!IsAble())
		return;
	int result = CPhidgetAdvancedServo_setAcceleration(m_TheCPhidgetAdvancedServo, indexServo, newAccMax);
}