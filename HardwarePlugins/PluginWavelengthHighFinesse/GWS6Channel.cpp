#include "GWS6Channel.h"
#include "GWavelengthMeterWS6.h"

G_REGISTER_HARD_DEVICE_CLASS(GWS6Channel)

GWS6Channel::GWS6Channel(QString uniqueIdentifierName, QObject* parent)
	: GHardDevice(uniqueIdentifierName, parent)
	, m_LastMeasure(QString("Lambda-") + uniqueIdentifierName.right(1), this, GParam::ReadOnly)
	, m_DoMonitor("Monitor", this)
{
	m_LastMeasure.SetDisplayDecimals(5);
	m_LastMeasure.SetHardLimits(-999.0, 9999.0);
}

GWS6Channel::~GWS6Channel()
{

}

void GWS6Channel::PopulateDeviceWidget(GDeviceWidget* theDeviceWidget )
{
	QBoxLayout* pLayV = new QVBoxLayout();
	QBoxLayout* pLayH = new QHBoxLayout();
	theDeviceWidget->AddSubLayout(pLayV);
	QDoubleSpinBox* pSpinBoxLastMeasure = m_LastMeasure.ProvideNewParamSpinBox(theDeviceWidget);
	QLabel* nameLabel = m_LastMeasure.ProvideNewLabel(theDeviceWidget);
	pLayH->addWidget(nameLabel);
	pLayH->addWidget(pSpinBoxLastMeasure);
	QCheckBox* pEnableMonitorBox = m_DoMonitor.ProvideNewParamCheckBox(theDeviceWidget, "Monitor");
	pLayV->addWidget(pEnableMonitorBox);
	pLayV->addLayout(pLayH);
}

void GWS6Channel::IncomingUpdate( double newWaveLength )
{
	if(m_DoMonitor)
		m_LastMeasure = newWaveLength;
}