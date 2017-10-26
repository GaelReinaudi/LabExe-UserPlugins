#include "GPhidgetInterfaceKitModule.h"
#include "GPhidgetManager.h"
#include "GPhidgetSensor.h"
#include "GPhidgetDigitalInput.h"

#include "GPhidget21.h"

G_REGISTER_HARD_DEVICE_CLASS(GPhidgetInterfaceKitModule)

int __stdcall SensorValueChangeHandler(PhidgetInterfaceKitHandle IFK, void *pPhiMod, int indexSensor, int Value)
{
	GPhidgetInterfaceKitModule* pPhidgetModule = (GPhidgetInterfaceKitModule*)pPhiMod;
	if(pPhidgetModule)// && pPhidgetModule->IsAble())
		pPhidgetModule->TriggeredSensorValueChanged(indexSensor, Value);
	return 0;
}

int __stdcall DigitalInputValueChangeHandler(PhidgetInterfaceKitHandle IFK, void *pPhiMod, int indexDigIn, int Value)
{
	GPhidgetInterfaceKitModule* pPhidgetModule = (GPhidgetInterfaceKitModule*)pPhiMod;
	if(pPhidgetModule)// && pPhidgetModule->IsAble())
		pPhidgetModule->TriggeredDigitalInputValueChanged(indexDigIn, Value);
	return 0;
}

int __stdcall DigitalOutputValueChangeHandler(PhidgetInterfaceKitHandle IFK, void *pPhiMod, int indexDigOut, int Value)
{
	GPhidgetInterfaceKitModule* pPhidgetModule = (GPhidgetInterfaceKitModule*)pPhiMod;
	if(pPhidgetModule)// && pPhidgetModule->IsAble())
		pPhidgetModule->TriggeredDigitalOutputValueChanged(indexDigOut, Value);
	return 0;
}

GPhidgetInterfaceKitModule::GPhidgetInterfaceKitModule(QString uniqueIdentifierName, QObject *parent)
	: GPhidgetModule(uniqueIdentifierName, parent)
	, m_ThePhidgetInterfaceKit(0)
	, m_NumberSensors(0)
	, m_NumberDigitalInputs(0)
	, m_NumberDigitalOutputs(0)
{
	m_SerialNumber = GPhidgetManager::GetSerialFromPhidgetIdentifier(UniqueSystemID());
	if(!m_SerialNumber)
		return;
	//create the advanced servo object
	PhidgetInterfaceKit_create(&m_ThePhidgetInterfaceKit);
	PhidgetInterfaceKit_setRatiometric(m_ThePhidgetInterfaceKit, 1);
}

GPhidgetInterfaceKitModule::~GPhidgetInterfaceKitModule()
{
	if(!m_ThePhidgetInterfaceKit)
		return;
	m_Sensors.clear();
	m_DigInputs.clear();
	m_DigOutputs.clear();
	//... terminate the program so we will close the phidget and delete the object we created
	Phidget_close(ThePhidgetHandle());
	Phidget_delete(&ThePhidgetHandle());
	//all done, exit
}

void GPhidgetInterfaceKitModule::DelayedPhidgetInitialization()
{
	PhidgetInterfaceKit_set_OnSensorChangeHandler(m_ThePhidgetInterfaceKit, SensorValueChangeHandler, this);
	PhidgetInterfaceKit_set_OnInputChangeHandler(m_ThePhidgetInterfaceKit, DigitalInputValueChangeHandler, this);
	PhidgetInterfaceKit_set_OnOutputChangeHandler(m_ThePhidgetInterfaceKit, DigitalOutputValueChangeHandler, this);
	ConfigureWhenPluggedIn();
}

void GPhidgetInterfaceKitModule::ConfigureWhenPluggedIn()
{
	// get the number of sensors
	PhidgetInterfaceKit_getSensorCount(m_ThePhidgetInterfaceKit, &m_NumberSensors);
	PhidgetInterfaceKit_getInputCount(m_ThePhidgetInterfaceKit, &m_NumberDigitalInputs);
	PhidgetInterfaceKit_getOutputCount(m_ThePhidgetInterfaceKit, &m_NumberDigitalOutputs);
	CreateSubDevicesSensors();
	CreateSubDevicesDigitalInput();
	CreateSubDevicesDigitalOutput();

	for(int indexSensor = 0; indexSensor < m_NumberSensors; indexSensor++) {
		// sets the sensitivity of the device for triggering the SensorValueChangeHandler
		// and the data rate, see the manual for more info
		PhidgetInterfaceKit_setSensorChangeTrigger(m_ThePhidgetInterfaceKit, indexSensor, 0);
		PhidgetInterfaceKit_setDataRate(m_ThePhidgetInterfaceKit, indexSensor, 80);

		int theValue = 0;
		PhidgetInterfaceKit_getSensorValue(m_ThePhidgetInterfaceKit, indexSensor, &theValue);
		TriggeredSensorValueChanged(indexSensor, theValue);
		// just some info for debugging
		int dataRate = 0;
		PhidgetInterfaceKit_getDataRate(m_ThePhidgetInterfaceKit, indexSensor, &dataRate);
		qDebug() << dataRate;
	}

	for(int indexDigIn = 0; indexDigIn < m_NumberSensors; indexDigIn++) {
		int theValue = 0;
		PhidgetInterfaceKit_getInputState(m_ThePhidgetInterfaceKit, indexDigIn, &theValue);
		TriggeredDigitalInputValueChanged(indexDigIn, theValue);
	}

	emit IsAblenessMayHaveChanged(IsAble());
}

void GPhidgetInterfaceKitModule::PopulateDeviceWidget(GDeviceWidget* theDeviceWidget )
{
	// layout
	QLayout* sensorsLayout = theDeviceWidget->layout();
	if(!sensorsLayout)
		sensorsLayout = new QVBoxLayout(theDeviceWidget);
}

void GPhidgetInterfaceKitModule::TriggeredSensorValueChanged( int indexSensor, int theValue )
{
	// 	// you can querry the 12 bit value ! But on Interface kit 1018, it is only 10 bit so it doesn't make sense to use it, does it?
	// 	int the12BitRawValue;
	// 	PhidgetInterfaceKit_getSensorRawValue(m_ThePhidgetInterfaceKit, indexSensor, &the12BitRawValue);

	GPhidgetSensor* pTheSensor = Sensor(indexSensor);
	if(pTheSensor)
		pTheSensor->ModuleTriggeredValueChanged(theValue);
}

void GPhidgetInterfaceKitModule::TriggeredDigitalInputValueChanged( int indexDigIn, bool theValue )
{
	GPhidgetDigitalInput* pTheDigIn = DigitalInput(indexDigIn);
	if(pTheDigIn)
		pTheDigIn->ModuleTriggeredValueChanged(theValue);
}

void GPhidgetInterfaceKitModule::TriggeredDigitalOutputValueChanged( int indexDigOut, bool theValue )
{

}

void GPhidgetInterfaceKitModule::CreateSubDevicesSensors()
{
	if(!IsAble())
		return;
	m_Sensors.clear();
	for(int indexSensor = 0; indexSensor < m_NumberSensors; indexSensor++) {
		QString nameSensor = CreateUniqueSensorIdentifier(indexSensor);
		// if it already exist, lets not make it again.
		GDevice* pSensor = GetDeviceFromDeviceManager(nameSensor);
		// but let's make sure or set the correct parent module (in case it was created	at startup, without the module parent created...)
		if(pSensor)// && pSensor->parent() != this)
			pSensor->setParent(this);
		else
			pSensor = new GPhidgetSensor(nameSensor, this);
		m_Sensors.append(pSensor);
		disconnect(this, SIGNAL(IsAblenessMayHaveChanged(bool)), pSensor, SIGNAL(IsAblenessMayHaveChanged(bool)));
		connect(this, SIGNAL(IsAblenessMayHaveChanged(bool)), pSensor, SIGNAL(IsAblenessMayHaveChanged(bool)), Qt::QueuedConnection);
	}
}

void GPhidgetInterfaceKitModule::CreateSubDevicesDigitalInput()
{
	if(!IsAble())
		return;
	m_DigInputs.clear();
	for(int indexDigIn = 0; indexDigIn < m_NumberDigitalInputs; indexDigIn++) {
		QString nameDig = CreateUniqueDigitalInputIdentifier(indexDigIn);
		// if it already exist, lets not make it again.
		GDevice* pDigitalInput = GetDeviceFromDeviceManager(nameDig);
		// but let's make sure or set the correct parent module (in case it was created	at startup, without the module parent created...)
		if(pDigitalInput)// && pDigitalInput->parent() != this)
			pDigitalInput->setParent(this);
		else
			pDigitalInput = new GPhidgetDigitalInput(nameDig, this);
		m_DigInputs.append(pDigitalInput);
		disconnect(this, SIGNAL(IsAblenessMayHaveChanged(bool)), pDigitalInput, SIGNAL(IsAblenessMayHaveChanged(bool)));
		connect(this, SIGNAL(IsAblenessMayHaveChanged(bool)), pDigitalInput, SIGNAL(IsAblenessMayHaveChanged(bool)), Qt::QueuedConnection);
	}
}

void GPhidgetInterfaceKitModule::CreateSubDevicesDigitalOutput()
{
	if(!IsAble())
		return;
// 	m_DigOutputs.clear();
// 	for(int indexDigOut = 0; indexDigOut < m_NumberDigitalOutputs; indexDigOut++) {
// 		QString nameDig = CreateUniqueDigitalOutputIdentifier(indexDigOut);
// 		// if it already exist, lets not make it again.
// 		GDevice* pDigitalOutput = GetDeviceFromDeviceManager(nameDig);
// 		// but let's make sure or set the correct parent module (in case it was created	at startup, without the module parent created...)
// 		if(pDigitalOutput)// && pDigitalOutput->parent() != this)
// 			pDigitalOutput->setParent(this);
// 		else
// 			pDigitalOutput = new GPhidgetDigitalOutput(nameDig, this);
// 		m_DigOutputs.append(pDigitalOutput);
// 		disconnect(this, SIGNAL(IsAblenessMayHaveChanged(bool)), pDigitalOutput, SIGNAL(IsAblenessMayHaveChanged(bool)));
// 		connect(this, SIGNAL(IsAblenessMayHaveChanged(bool)), pDigitalOutput, SIGNAL(IsAblenessMayHaveChanged(bool)), Qt::QueuedConnection);
// 	}
}

bool GPhidgetInterfaceKitModule::IsAble() const
{
	if(GPhidgetModule::IsAble())
		if(m_ThePhidgetInterfaceKit)
			return true;
	return false;
}

QString GPhidgetInterfaceKitModule::CreateUniqueSensorIdentifier(int indexSensor) const {
	return UniqueSystemID() + QString("%1%2").arg(PHIDGET_SENSOR_NUMBER_SEPARATOR).arg(indexSensor);
}

GPhidgetSensor* GPhidgetInterfaceKitModule::Sensor( int indexSensor ) const
{
	if(indexSensor < m_Sensors.count())
		return qobject_cast<GPhidgetSensor*>(m_Sensors.at(indexSensor));
	return 0;
}

GPhidgetDigitalInput* GPhidgetInterfaceKitModule::DigitalInput( int indexDigIn )
{
	if(indexDigIn < m_DigInputs.count())
		return qobject_cast<GPhidgetDigitalInput*>(m_DigInputs.at(indexDigIn));
	return 0;
}

GPhidgetDigitalOutput* GPhidgetInterfaceKitModule::DigitalOutput( int indexDigOut )
{
//	if(indexDigOut < m_DigOutputs.count())
//		return qobject_cast<GPhidgetDigitalOutput*>(m_DigOutputs.at(indexDigOut));
	return 0;
}

QString GPhidgetInterfaceKitModule::CreateUniqueDigitalInputIdentifier( int indexDigIn )
{
	return UniqueSystemID() + QString("%1%2").arg(PHIDGET_DIGITAL_INPUT_NUMBER_SEPARATOR).arg(indexDigIn);
}

QString GPhidgetInterfaceKitModule::CreateUniqueDigitalOutputIdentifier( int indexDigOut )
{
	return UniqueSystemID() + QString("%1%2").arg(PHIDGET_DIGITAL_OUTPUT_NUMBER_SEPARATOR).arg(indexDigOut);
}