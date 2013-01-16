#include "GPxiBasicAnalogInput.h"
//2011-11-22 #include "logger.h"

G_REGISTER_HARD_DEVICE_CLASS(GPxiBasicAnalogInput)

GPxiBasicAnalogInput::GPxiBasicAnalogInput(QString uniqueIdentifierName, QObject* parentDevice)
	: GPxiChannel(uniqueIdentifierName, parentDevice)
	, m_Value(DefaultShortName(), this, GParam::ReadOnly)
{
//2011-11-22	SetParamToControl(m_Value);

//2011-11-22	m_pDataLogger = new GTimeDataLogger(Name(), &m_DummyWidgetToParentWidgets);
//2011-11-22	m_pDataLogger->setWindowTitle(Name() + " : Data Logger");
//2011-11-22	connect(m_pDataLogger, SIGNAL(NeedRefreshment()), this, SLOT(UpdateFromPhysicalInput()));
//2011-11-22	connect(this, SIGNAL(MeasuredValueChanged(double)), m_pDataLogger, SLOT(UpdateData(double)));
	connect(this, SIGNAL(NameChanged(QString)), &m_Value, SLOT(SetName(QString)));

	CString name(uniqueIdentifierName.toAscii());
	try{
		CNiDAQmxAIChannel chanAI = AIChannels.CreateVoltageChannel(name, "", DAQmxAITerminalConfigurationRse, -10.0, 10.0, DAQmxAIVoltageUnitsVolts);
	}
	catch (CNiDAQmxException *exception)
	{
		exception->ReportError();
		exception->Delete();
	}
}

GPxiBasicAnalogInput::~GPxiBasicAnalogInput()
{
}

void GPxiBasicAnalogInput::PopulateDeviceWidget(GDeviceWidget* theDeviceWidget )
{
	theDeviceWidget->DontDisplayTitle();
	// The spin box holding the value 
	QWidget* pSpinBox = m_Value.ProvideNewParamSpinBox(theDeviceWidget);

	// Button to access the settings
	QPushButton* pSettingButton = new QPushButton("set...", theDeviceWidget);
	pSettingButton->setMaximumSize(pSpinBox->sizeHint());
//2011-11-22	connect(pSettingButton, SIGNAL(pressed()), m_pDataLogger, SLOT(show()));

	// A QFormLayout, in which we place the label and the spinbox associated with the GParam
	QFormLayout* valueLayout = new QFormLayout();
	theDeviceWidget->AddSubLayout(valueLayout);
	QLabel* nameLabel = m_Value.ProvideNewLabel(theDeviceWidget);
	valueLayout->addRow(nameLabel, pSpinBox);

	QFormLayout* settingLayout = new QFormLayout();
	theDeviceWidget->AddSubLayout(settingLayout);
	settingLayout->addWidget(pSettingButton);

//	UpdateFromPhysicalInput();
}

double GPxiBasicAnalogInput::UpdateFromPhysicalInput()
{
	try
	{
		// Create a writer
		CNiDAQmxAnalogSingleChannelReader m_reader(Stream);
		// And write immediately
		m_Value = m_reader.ReadSingleSample();
//		// Wait until the I/O completes before destroying the task
//		WaitUntilDone(-1);
		emit MeasuredValueChanged(m_Value);
	}
	catch (CNiDAQmxException *exception)
	{
		exception->ReportError();
		exception->Delete();
//		return false;
	}
	return m_Value;
}

void GPxiBasicAnalogInput::PopulateContextMenu( QMenu* pTheMenu )
{
	pTheMenu->addSeparator()->setText(tr("Basic Input"));
	GPxiChannel::PopulateContextMenu(pTheMenu);
}