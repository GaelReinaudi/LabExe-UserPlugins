#include "GPhidgetSensor.h"

G_REGISTER_HARD_DEVICE_CLASS(GPhidgetSensor)

GPhidgetSensor::GPhidgetSensor(QString uniqueIdentifierName, QObject *parent)
	: GHardDevice(uniqueIdentifierName, parent)
	, m_LastMeasure(Name(), this, GParam::ReadOnly)
{
	m_LastMeasure.SetDisplayDecimals(0);
	m_LastMeasure.SetHardLimits(-999.0, 9999.0);

	connect(this, SIGNAL(NameChanged(QString)), &m_LastMeasure, SLOT(SetName(QString)));
}

GPhidgetSensor::~GPhidgetSensor()
{

}

void GPhidgetSensor::PopulateDeviceWidget(GDeviceWidget* theDeviceWidget )
{
//	theDeviceWidget->DontDisplayTitle();
	QBoxLayout* pLay = new QHBoxLayout();
	theDeviceWidget->AddSubLayout(pLay);

	QDoubleSpinBox* pSpinBox = m_LastMeasure.ProvideNewParamSpinBox(theDeviceWidget);
	QLabel* nameLabel = m_LastMeasure.ProvideNewLabel(theDeviceWidget);
	pLay->addWidget(nameLabel);
	pLay->addWidget(pSpinBox);
}

void GPhidgetSensor::ModuleTriggeredValueChanged( int theValue )
{
	m_LastMeasure = theValue;
}