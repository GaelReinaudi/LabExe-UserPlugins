#include "GPhidgetTouchRotationModule.h"
#include "GPhidgetManager.h"
#include "param.h"

G_REGISTER_HARD_DEVICE_CLASS(GPhidgetTouchRotationModule)

GPhidgetTouchRotationModule::GPhidgetTouchRotationModule(QString uniqueIdentifierName, QObject *parent)
	: GPhidgetInterfaceKitModule(uniqueIdentifierName, parent)
	, m_Proximity("Proximity", 0)
	, m_Touching("Touching", 0)
	, m_TouchCount("Touched", 0)
	, m_TouchTicks("Touch Tics", 0)
	, m_CumulativeTicks("Total Tics", this)
	, m_lastValue(-1)
{
	m_TouchCount.SetHardLimits(0, 1e4);
	m_CumulativeTicks.SetHardLimits(-1e5, 1e6);
	m_TouchTicks.SetHardLimits(-1e5, 1e5);
}

GPhidgetTouchRotationModule::~GPhidgetTouchRotationModule()
{
}

void GPhidgetTouchRotationModule::TriggeredSensorValueChanged( int indexSensor, int theValue )
{
	GPhidgetInterfaceKitModule::TriggeredSensorValueChanged(indexSensor, theValue);
	if(indexSensor != 0) {
		return;
	}
	if(!m_Touching) {
		return;
	}
	// ticking up or down
	int tick = 0;
	if(m_lastValue == -1) {
		m_lastValue = theValue;
	}

	int delta = theValue - m_lastValue;
	// if cycling back down when passing the 1000 limit
	if(delta < -600) {
		delta += 1000;
	}
	// conversely...
	if(delta > 600) {
		delta -= 1000;
	}

	m_lastValue = theValue;
	m_CumulativeTicks += delta / 8;
	m_TouchTicks += delta / 8;
}

void GPhidgetTouchRotationModule::TriggeredDigitalInputValueChanged( int indexDigIn, bool theValue )
{
	GPhidgetInterfaceKitModule::TriggeredDigitalInputValueChanged(indexDigIn, theValue);
	switch(indexDigIn) {
	case 1:
		m_Proximity = theValue;
		break;
	case 0:
		m_Touching = theValue;
		// if you start touching, we try to reset the value for the rotation
		if(!m_Touching && theValue) {
			m_lastValue = -1;
			m_TouchTicks = 0;
			m_TouchCount += 1;
		}
		break;
	}
}

void GPhidgetTouchRotationModule::PopulateDeviceWidget( GDeviceWidget* theDeviceWidget )
{
	QFormLayout* pLay = new QFormLayout();
	theDeviceWidget->AddSubLayout(pLay);

	pLay->addRow(m_Proximity.ProvideNewLabel(theDeviceWidget), m_Proximity.ProvideNewParamCheckBox(theDeviceWidget, ""));
	pLay->addRow(m_Touching.ProvideNewLabel(theDeviceWidget), m_Touching.ProvideNewParamCheckBox(theDeviceWidget, ""));
	pLay->addRow(m_TouchCount.ProvideNewLabel(theDeviceWidget), m_TouchCount.ProvideNewParamSpinBox(theDeviceWidget));
	pLay->addRow(m_TouchTicks.ProvideNewLabel(theDeviceWidget), m_TouchTicks.ProvideNewParamSpinBox(theDeviceWidget));
	pLay->addRow(m_CumulativeTicks.ProvideNewLabel(theDeviceWidget), m_CumulativeTicks.ProvideNewParamSpinBox(theDeviceWidget));
}