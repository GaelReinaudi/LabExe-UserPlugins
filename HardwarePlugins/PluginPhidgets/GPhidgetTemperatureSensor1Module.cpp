#include "GPhidgetTemperatureSensor1Module.h"
#include "GPhidgetManager.h"
#include "param.h"

#include "GPhidget21.h"

G_REGISTER_HARD_DEVICE_CLASS(GPhidgetTemperatureSensor1Module)

int __stdcall TemperatureChangeHandler(PhidgetTemperatureSensorHandle IFK, void *pPhiMod, int indexSensor, double Value)
{
	GPhidgetTemperatureSensor1Module* pPhidgetModule = (GPhidgetTemperatureSensor1Module*)pPhiMod;
	if(pPhidgetModule)// && pPhidgetModule->IsAble())
		pPhidgetModule->TemperatureChanged(indexSensor, Value);
	return 0;
}

GPhidgetTemperatureSensor1Module::GPhidgetTemperatureSensor1Module(QString uniqueIdentifierName, QObject *parent)
	: GPhidgetModule(uniqueIdentifierName, parent)
	, m_ThePhidgetTemperatureSensor1(0)
	, m_NumberSensors(0)
	, m_Temperature("Probe Temp [C]", this, GParam::ReadOnly)
	, m_AmbientTemperature("Ambient Temp [C]", this, GParam::ReadOnly)
{
	m_SerialNumber = GPhidgetManager::GetSerialFromPhidgetIdentifier(UniqueSystemID());
	if(!m_SerialNumber)
		return;
	//create the advanced servo object
	PhidgetTemperatureSensor_create(&m_ThePhidgetTemperatureSensor1);
}

GPhidgetTemperatureSensor1Module::~GPhidgetTemperatureSensor1Module()
{
	if(!m_ThePhidgetTemperatureSensor1)
		return;
	//... terminate the program so we will close the phidget and delete the object we created
	Phidget_close(ThePhidgetHandle());
	Phidget_delete(&ThePhidgetHandle());
	//all done, exit
}

void GPhidgetTemperatureSensor1Module::DelayedPhidgetInitialization()
{
	//Registers a callback that will run if the Temperature changes by more than the Temperature trigger.
	//Requires the handle for the Temperature Sensor, the function that will be called, and a arbitrary pointer that will be supplied to the callback function (may be NULL).
	PhidgetTemperatureSensor_set_OnTemperatureChangeHandler(m_ThePhidgetTemperatureSensor1, TemperatureChangeHandler, this);
	ConfigureWhenPluggedIn();
}

void GPhidgetTemperatureSensor1Module::ConfigureWhenPluggedIn()
{
	// get the number of sensors
	PhidgetTemperatureSensor_getTemperatureInputCount(m_ThePhidgetTemperatureSensor1, &m_NumberSensors);
	CreateSubDevicesSensors();
//	CreateSubDevicesDigitalInput();
//	CreateSubDevicesDigitalOutput();

	double theValue = 0;
	PhidgetTemperatureSensor_getTemperature(m_ThePhidgetTemperatureSensor1, &theValue);
	AmbientTemperatureChanged(theValue);

	for(int indexSensor = 0; indexSensor < m_NumberSensors; indexSensor++) {
		// sets the sensitivity of the device for triggering the TemperatureChangeHandler
		// and the data rate, see the manual for more info
		PhidgetTemperatureSensor_setTemperatureChangeTrigger(m_ThePhidgetTemperatureSensor1, indexSensor, 0.02);
		PhidgetTemperatureSensor_setThermocoupleType(m_ThePhidgetTemperatureSensor1, indexSensor, PHIDGET_TEMPERATURE_SENSOR_K_TYPE);

		PhidgetTemperatureSensor_getTemperature(m_ThePhidgetTemperatureSensor1, indexSensor, &theValue);
		TemperatureChanged(indexSensor, theValue);
	}

	emit IsAblenessMayHaveChanged(IsAble());
}

void GPhidgetTemperatureSensor1Module::PopulateDeviceWidget(GDeviceWidget* theDeviceWidget )
{
	QFormLayout* pLay = new QFormLayout();
	theDeviceWidget->AddSubLayout(pLay);

	pLay->addRow(m_AmbientTemperature.ProvideNewLabel(theDeviceWidget), m_AmbientTemperature.ProvideNewParamSpinBox(theDeviceWidget));
	pLay->addRow(m_Temperature.ProvideNewLabel(theDeviceWidget), m_Temperature.ProvideNewParamSpinBox(theDeviceWidget));
}

void GPhidgetTemperatureSensor1Module::AmbientTemperatureChanged(double theValue)
{
	m_AmbientTemperature = theValue;
}

void GPhidgetTemperatureSensor1Module::TemperatureChanged( int indexSensor, double theValue )
{
	if(indexSensor == 0)
		m_Temperature = theValue;

	PhidgetTemperatureSensor_getTemperature(m_ThePhidgetTemperatureSensor1, &theValue);
	AmbientTemperatureChanged(theValue);
}

void GPhidgetTemperatureSensor1Module::CreateSubDevicesSensors()
{
	if(!IsAble())
		return;
	m_Sensors.clear();
	for(int indexSensor = 0; indexSensor < m_NumberSensors; indexSensor++) {
// 		QString nameSensor = CreateUniqueSensorIdentifier(indexSensor);
// 		// if it already exist, lets not make it again.
// 		GDevice* pSensor = GetDeviceFromDeviceManager(nameSensor);
// 		// but let's make sure or set the correct parent module (in case it was created	at startup, without the module parent created...)
// 		if(pSensor)// && pSensor->parent() != this)
// 			pSensor->setParent(this);
// 		else
// 			pSensor = new GPhidgetSensor(nameSensor, this);
// 		m_Sensors.append(pSensor);
// 		disconnect(this, SIGNAL(IsAblenessMayHaveChanged(bool)), pSensor, SIGNAL(IsAblenessMayHaveChanged(bool)));
// 		connect(this, SIGNAL(IsAblenessMayHaveChanged(bool)), pSensor, SIGNAL(IsAblenessMayHaveChanged(bool)), Qt::QueuedConnection);
	}
}

// QString GPhidgetTemperatureSensor1Module::CreateUniqueSensorIdentifier(int indexSensor) const {
// 	return UniqueSystemID() + QString("%1%2").arg(PHIDGET_SENSOR_NUMBER_SEPARATOR).arg(indexSensor);
// }
// 
// QString GPhidgetTemperatureSensor1Module::CreateUniqueDigitalInputIdentifier( int indexDigIn )
// {
// 	return UniqueSystemID() + QString("%1%2").arg(PHIDGET_DIGITAL_INPUT_NUMBER_SEPARATOR).arg(indexDigIn);
// }
// 
// QString GPhidgetTemperatureSensor1Module::CreateUniqueDigitalOutputIdentifier( int indexDigOut )
// {
// 	return UniqueSystemID() + QString("%1%2").arg(PHIDGET_DIGITAL_OUTPUT_NUMBER_SEPARATOR).arg(indexDigOut);
// }

bool GPhidgetTemperatureSensor1Module::IsAble() const
{
	if(GPhidgetModule::IsAble())
		if(m_ThePhidgetTemperatureSensor1)
			return true;
	return false;
}
