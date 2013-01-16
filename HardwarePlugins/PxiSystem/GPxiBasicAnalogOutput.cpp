#include "GPxiBasicAnalogOutput.h"

G_REGISTER_HARD_DEVICE_CLASS(GPxiBasicAnalogOutput)

#define DEFAULT_LIMIT_MIN (-10.0)
#define DEFAULT_LIMIT_MAX (10.0)

GPxiBasicAnalogOutput::GPxiBasicAnalogOutput(QString uniqueIdentifierName, QObject* parentDevice)
	: GPxiChannel(uniqueIdentifierName, parentDevice)
	, m_SetPoint(DefaultShortName(), this)
{
	m_SetPoint.SetTypicalStep(0.01);
	m_SetPoint.SetDisplayDecimals(3);
	m_SetPoint.SetHardLimits(DEFAULT_LIMIT_MIN, DEFAULT_LIMIT_MAX);

	CString name(uniqueIdentifierName.toAscii());
	try {
		AOChannels.CreateVoltageChannel(name, "", DEFAULT_LIMIT_MIN, DEFAULT_LIMIT_MAX, DAQmxAOVoltageUnitsVolts);
	}
	catch (CNiDAQmxException *exception) {
		exception->ReportError();
		exception->Delete();
	}
	connect(&m_SetPoint, SIGNAL(ValueUpdated(double)), this, SLOT(ChangeSetPoint(double)));
	connect(this, SIGNAL(NameChanged(QString)), &m_SetPoint, SLOT(SetName(QString)));
}

GPxiBasicAnalogOutput::~GPxiBasicAnalogOutput()
{

}

void GPxiBasicAnalogOutput::PopulateDeviceWidget(GDeviceWidget* theDeviceWidget )
{
	theDeviceWidget->DontDisplayTitle();
	// The spin box holding the value of the setpoint
	QDoubleSpinBox* pSetPointSpinBox = m_SetPoint.ProvideNewParamSpinBox(theDeviceWidget);

	// A QFormLayout, in which we place the label and the spinbox 
	QFormLayout* valueLayout = new QFormLayout();
	theDeviceWidget->AddSubLayout(valueLayout);
	QLabel* nameLabel = m_SetPoint.ProvideNewLabel(theDeviceWidget);
	valueLayout->addRow(nameLabel, pSetPointSpinBox);
}

void GPxiBasicAnalogOutput::ChangeSetPoint( double newValue )
{
	if(!gEqual(newValue, m_SetPoint)) 
		m_SetPoint = newValue;

	if(UpdatePhysicalOutput(newValue))
		emit SetPointChanged(newValue);
}

bool GPxiBasicAnalogOutput::UpdatePhysicalOutput( double newSetPoint )
{
	try {
		// Create a writer
		CNiDAQmxAnalogSingleChannelWriter m_writer(Stream);
		// And write immediately
		m_writer.WriteSingleSample(true, newSetPoint);
		// Wait until the I/O completes before destroying the task
		WaitUntilDone(-1);
	}
	catch (CNiDAQmxException *exception) {
		exception->ReportError();
		exception->Delete();
		return false;
	}
	return true;
}
