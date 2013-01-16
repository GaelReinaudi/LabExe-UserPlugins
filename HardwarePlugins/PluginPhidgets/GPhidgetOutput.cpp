#include "GPhidgetOutput.h"
#include "GPhidgetAnalogOutModule.h"

G_REGISTER_HARD_DEVICE_CLASS(GPhidgetOutput)

GPhidgetOutput::GPhidgetOutput(QString uniqueIdentifierName, QObject *parent)
	: GHardDevice(uniqueIdentifierName, parent)
	, m_OutValue(Name(), this)
{
	m_OutValue.SetDisplayDecimals(3);
	m_OutValue.SetHardLimits(-99.999, 99.999);

	connect(this, SIGNAL(NameChanged(QString)), &m_OutValue, SLOT(SetName(QString)));
	connect(&m_OutValue, SIGNAL(ValueUpdated(double)), this, SLOT(SetOutputValue(double)));

//	SetOutputValue(double(m_OutValue));
	emit IsAblenessMayHaveChanged(IsAble());
}

GPhidgetOutput::~GPhidgetOutput()
{

}

void GPhidgetOutput::PopulateDeviceWidget(GDeviceWidget* theDeviceWidget )
{
	QBoxLayout* pLay = new QHBoxLayout();
	theDeviceWidget->AddSubLayout(pLay);

	QDoubleSpinBox* pSpinBox = m_OutValue.ProvideNewParamSpinBox(theDeviceWidget);
	QLabel* nameLabel = m_OutValue.ProvideNewLabel(theDeviceWidget);
	pLay->addWidget(nameLabel);
	pLay->addWidget(pSpinBox);
}

GPhidgetAnalogOutModule* GPhidgetOutput::ParentModule() const
{
	return qobject_cast<GPhidgetAnalogOutModule*>(parent());
}

void GPhidgetOutput::SetOutputValue( double newValue )
{
	if(!IsAble())
		return;
	ParentModule()->SetNewOutputValue(IndexOutput(), newValue);
}

bool GPhidgetOutput::IsAble() const
{
	if(ParentModule())
		if(ParentModule()->IsAble())
			return true;
	return false;
}

int GPhidgetOutput::IndexOutput() const
{
	return ParentModule()->GetIndexOutputFromPhidgetOutputIdentifier(UniqueSystemID());
}
