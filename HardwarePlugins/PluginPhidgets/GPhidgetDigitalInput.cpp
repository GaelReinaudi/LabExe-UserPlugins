#include "GPhidgetDigitalInput.h"

G_REGISTER_HARD_DEVICE_CLASS(GPhidgetDigitalInput)

GPhidgetDigitalInput::GPhidgetDigitalInput(QString uniqueIdentifierName, QObject *parent)
	: GHardDevice(uniqueIdentifierName, parent)
	, m_State("state", this, GParam::ReadOnly)
	, m_CountSwitchTrue("count", this, GParam::ReadOnly)
{

}

GPhidgetDigitalInput::~GPhidgetDigitalInput()
{

}

void GPhidgetDigitalInput::PopulateDeviceWidget(GDeviceWidget* theDeviceWidget )
{
	QFormLayout* pLay = new QFormLayout();
	theDeviceWidget->AddSubLayout(pLay);

	QWidget* pCheckBox = m_State.ProvideNewParamCheckBox(theDeviceWidget, "");
	QLabel* nameCheckBox = m_State.ProvideNewLabel(theDeviceWidget);
	pLay->addRow(nameCheckBox, pCheckBox);
	QWidget* pSpinBox = m_CountSwitchTrue.ProvideNewParamSpinBox(theDeviceWidget);
	QLabel* nameSpinBox = m_CountSwitchTrue.ProvideNewLabel(theDeviceWidget);
	pLay->addRow(nameSpinBox, pSpinBox);
}

void GPhidgetDigitalInput::ModuleTriggeredValueChanged( int theValue )
{
	m_State = theValue;
	if(theValue)
		m_CountSwitchTrue += 1;
}