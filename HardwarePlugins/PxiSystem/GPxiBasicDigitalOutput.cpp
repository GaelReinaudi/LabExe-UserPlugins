#include "GPxiBasicDigitalOutput.h"
#include "GDAQmxModule.h"
#include "Param/GParamBool.h"

GPxiBasicDigitalOutput::GPxiBasicDigitalOutput(QString uniqueIdentifierName, QObject* parentDevice)
	: GPxiChannel(uniqueIdentifierName, parentDevice)
	, m_SetPoint(DefaultShortName(), this)
{
	ReName(DefaultShortName());

	CString name(uniqueIdentifierName.toAscii());
	try {
		DOChannels.CreateChannel(name, "", DAQmxOneChannelForEachLine);
	}
	catch (CNiDAQmxException *exception) {
		exception->ReportError();
		exception->Delete();
	}
	connect(&m_SetPoint, SIGNAL(ValueUpdated(bool)), this, SLOT(ChangeSetPoint(bool)));
	connect(this, SIGNAL(NameChanged(QString)), &m_SetPoint, SLOT(SetName(QString)));
}

GPxiBasicDigitalOutput::~GPxiBasicDigitalOutput()
{

}

void GPxiBasicDigitalOutput::PopulateDeviceWidget(GDeviceWidget* theDeviceWidget )
{
	theDeviceWidget->DontDisplayTitle();
	// The button holding the value of the setpoint
	QWidget* pSetPointButton = m_SetPoint.ProvideNewParamWidget(theDeviceWidget);

	// A QFormLayout, in which we place the label and the spinbox 
	QFormLayout* valueLayout = new QFormLayout();
	theDeviceWidget->AddSubLayout(valueLayout);
	QLabel* nameLabel = m_SetPoint.ProvideNewLabel(theDeviceWidget);
	valueLayout->addRow(nameLabel, pSetPointButton);
}

void GPxiBasicDigitalOutput::ChangeSetPoint( bool newValue )
{
	if(newValue != m_SetPoint) 
		m_SetPoint = newValue;

	if(UpdatePhysicalOutput(newValue))
		emit SetPointChanged(newValue);
}

bool GPxiBasicDigitalOutput::UpdatePhysicalOutput( bool newSetPoint )
{
	try {
		// Create a writer
		CNiDAQmxDigitalSingleChannelWriter m_writer(Stream);
		// And write immediately
		m_writer.WriteSingleSampleSingleLine(true, newSetPoint);
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

QString GPxiBasicDigitalOutput::DefaultShortName() const
{
	QString thename = UniqueSystemID();
	if(!ParentModule())
		return thename;
	int chassisNum = ParentModule()->ChassisNumber();
	int slotNum = ParentModule()->SlotNumber();

	QStringList strpxiName = thename.split("/");
	QString strLine = strpxiName.takeLast();
	QString strPort = strpxiName.takeLast();
	int numLine = strLine.remove("line").toInt();
	int numPort = strPort.remove("port").toInt();
	int numDo = numPort * 8 + numLine;
	return QString("S%1-do%2").arg(slotNum).arg(numDo, 2, 10, QChar('0'));
}