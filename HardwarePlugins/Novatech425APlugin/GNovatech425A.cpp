#include "GNovatech425A.h"
#include "GNovatech425AWidget.h"
#include <stdio.h>
#include <QMutexLocker>
#include "hled.h"

//Needed for "OnDataAvailable"

//^Needed for "OnDataAvailable"

GNovatech425A::GNovatech425A(QString uniqueIdentifierName, QObject *parent)
	: GHardDevice(uniqueIdentifierName, parent)
	, m_SetComPort("Com port: ", this)
	, m_PortName("Port name", this)
	//, m_WriteString("Command", this)
	, m_pExtSerialPort(0)

	, m_BaudIndex("Baud Index", this)
	, m_FlowIndex("Flow Index", this)
	, m_ParIndex("Parity Index", this)
	, m_DataIndex("Data Bits", this)
	, m_StopIndex("Stop Bits", this)

	, m_Settings("NovaTech Settings", this)
	, m_DisplaySettings("This name won't show up...", this)
	, m_ComPortSettings("Com Port Settings", this)
	, m_Reset("Reset NovaTech", this)
	, m_FreqSine("Freq (Sine):", this)
	, m_ListPorts("List Available Ports", this)

	, m_FirstTime("First Time", this)

	, m_SetExtRef("Clock source", this)	
{
	m_pExtSerialPort = new QextSerialPort(QextSerialPort::EventDriven);
}

void GNovatech425A::PopulateDeviceWidget(GDeviceWidget* theDeviceWidget )
{
 	QWidget* pWid = new GNovatech425AWidget(this, theDeviceWidget);
	QBoxLayout* pLay = new QVBoxLayout();
	theDeviceWidget->AddSubLayout(pLay);
	pLay->addWidget(pWid);

	//NovaTech-Specific Settings:
	m_SettingsWidget.ui.parityBox->setCurrentIndex(2);
	m_SettingsWidget.ui.flowBox->setCurrentIndex(2);
	m_SettingsWidget.ui.baudBox->setCurrentIndex(7);
	m_SettingsWidget.ui.dataBox->setCurrentIndex(3);
	m_SettingsWidget.ui.stopBox->setCurrentIndex(0);

	connect(&m_SetComPort, SIGNAL(ValueUpdated(QString)), this, SLOT(ConnectToPort()));
}

GNovatech425A::~GNovatech425A()
{

}


void GNovatech425A::LatterInitialization()
{
	//emit StatusUpdate("NovaTech Com Port Settings:\n***(confirm these)***\n19.2 kBaud\nSoftware flow control\nNo Parity\n8 Data Bits\n1 Stop Bit\n");
	PortList();
	
	//m_pControllerWidget->ui->pPortNameLineEdit->setText("WHOA!");

	/*m_SettingsWidget.ui.baudBox->setCurrentIndex(m_BaudIndex);
	m_SettingsWidget.ui.flowBox->setCurrentIndex(m_FlowIndex);
	m_SettingsWidget.ui.parityBox->setCurrentIndex(m_ParIndex);
	m_SettingsWidget.ui.dataBox->setCurrentIndex(m_DataIndex);*/
	//m_SettingsWidget.ui.stopBox->setCurrentIndex(m_StopIndex);

	

	connect(&m_ListPorts, SIGNAL(ValueUpdated(bool)), this, SLOT(PortListCall()));
	connect(&m_Reset, SIGNAL(ValueUpdated(bool)), this, SLOT(ResetNovaTech()));
	connect(&m_SetExtRef, SIGNAL(ValueUpdated(bool)), this, SLOT(SetClockSource(bool)));
	connect(&m_ComPortSettings, SIGNAL(ValueUpdated(bool)), this, SLOT(ShowPortSettings()));
	

	//Com Port Settings buttons...
	connect(m_SettingsWidget.ui.baudBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setNewBaudRate()));
	connect(m_SettingsWidget.ui.flowBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setNewFlowControl()));
	connect(m_SettingsWidget.ui.parityBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setNewParity()));
	connect(m_SettingsWidget.ui.dataBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setNewDataBits()));
	connect(m_SettingsWidget.ui.stopBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setNewStopBits()));

	SetClockSource(m_SetExtRef);
	ClockLEDisGreen();//MICKEY (2016-02-12): Should start out green, light will only turn red when frequency is 
                      //incremented or Novatech 425A settings are queried.
	m_DisplaySettings = 0;

	//ConnectToPort();
}

void GNovatech425A::ConnectToPort()

{	
	//if(m_pExtSerialPort)
	//{
	//	m_pExtSerialPort->flush();
	//	m_pExtSerialPort->reset();
	//	m_pExtSerialPort->close();
	//	delete m_pExtSerialPort;
	//	m_pExtSerialPort = new QextSerialPort(QextSerialPort::EventDriven);
	//}

	m_pExtSerialPort->setPortName(m_SetComPort);

	m_CurrentStatus.chop(m_CurrentStatus.length()+100);//Resetting everything...
	m_Bytes.chop(m_Bytes.length()+100);//Resetting everything...

	if(m_pExtSerialPort->open(QIODevice::ReadWrite) == true) 
	{
		m_pExtSerialPort->flush();

		connect(m_pExtSerialPort, SIGNAL(readyRead()), this, SLOT(onReadyRead()));
		connect(m_pExtSerialPort, SIGNAL(dsrChanged(bool)), this, SLOT(onDsrChanged(bool)));

		if (!(m_pExtSerialPort->lineStatus() & LS_DSR))
		{
			emit StatusUpdate("warning: device is not turned on");
		}
		emit StatusUpdate("listening for data on "+m_pExtSerialPort->portName());
		emit LEDisGreen();
	}
	else 
	{
		emit StatusUpdate("device failed to open:"+m_pExtSerialPort->errorString());
	}

	setNewBaudRate();
	//m_pExtSerialPort->setBaudRate(BAUD19200);//I've changed this from 9600 to 19200, the
	//factory default setting for the NovaTech.
	setNewFlowControl();
	//m_pExtSerialPort->setFlowControl(FLOW_OFF);
	setNewParity();
	//m_pExtSerialPort->setParity(PAR_NONE);
	setNewDataBits();
	//m_pExtSerialPort->setDataBits(DATA_8);
	setNewStopBits();
	//m_pExtSerialPort->setStopBits(STOP_1);//Changed from STOP_2 to STOP_1, the NovaTech default.


	connect(&m_FreqSine, SIGNAL(ValueUpdated(double)), this, SLOT(SetNovaTechFreq0(double)));
	connect(&m_Settings, SIGNAL(ValueUpdated(bool)), this, SLOT(QueryCurrentSettings()));
}



void GNovatech425A::setNewFlowControl()
{
	m_FlowIndex = m_SettingsWidget.ui.flowBox->currentIndex();
	switch(m_FlowIndex.IntValue())
	{
	case 0:
		m_pExtSerialPort->setFlowControl(FLOW_OFF);
		break;
	case 1:
		m_pExtSerialPort->setFlowControl(FLOW_HARDWARE);
		break;
	case 2:
		m_pExtSerialPort->setFlowControl(FLOW_XONXOFF);
		break;
	default:
		break;
	}
}


void GNovatech425A::setNewBaudRate()
{
	m_BaudIndex = m_SettingsWidget.ui.baudBox->currentIndex();
	switch(m_BaudIndex.IntValue())
	{
	case 0:
		m_pExtSerialPort->setBaudRate(BAUD110);
		break;
	case 1:
		m_pExtSerialPort->setBaudRate(BAUD300);
		break;
	case 2:
		m_pExtSerialPort->setBaudRate(BAUD600);
		break;
	case 3:
		m_pExtSerialPort->setBaudRate(BAUD1200);
		break;
	case 4:
		m_pExtSerialPort->setBaudRate(BAUD2400);
		break;
	case 5:
		m_pExtSerialPort->setBaudRate(BAUD4800);
		break;
	case 6:
		m_pExtSerialPort->setBaudRate(BAUD9600);
		break;
	case 7:
		m_pExtSerialPort->setBaudRate(BAUD19200);
		break;
	case 8:
		m_pExtSerialPort->setBaudRate(BAUD38400);
		break;
	case 9:
		m_pExtSerialPort->setBaudRate(BAUD57600);
		break;
	case 10:
		m_pExtSerialPort->setBaudRate(BAUD115200);
		break;
	default:
		break;
	}
}

void GNovatech425A::setNewParity()
{
	m_ParIndex = m_SettingsWidget.ui.parityBox->currentIndex();
	switch(m_ParIndex.IntValue())
	{
	case 0:
		m_pExtSerialPort->setParity(PAR_SPACE);
		break;
	case 1:
		m_pExtSerialPort->setParity(PAR_MARK);
		break;
	case 2:
		m_pExtSerialPort->setParity(PAR_NONE);
		break;
	case 3:
		m_pExtSerialPort->setParity(PAR_EVEN);
		break;
	case 4:
		m_pExtSerialPort->setParity(PAR_ODD);
		break;
	default:
		break;
	}
}

void GNovatech425A::setNewDataBits()
{
	m_DataIndex = m_SettingsWidget.ui.dataBox->currentIndex();
	switch(m_DataIndex.IntValue())
	{
	case 0:
		m_pExtSerialPort->setDataBits(DATA_5);
		break;
	case 1:
		m_pExtSerialPort->setDataBits(DATA_6);
		break;
	case 2:
		m_pExtSerialPort->setDataBits(DATA_7);
		break;
	case 3:
		m_pExtSerialPort->setDataBits(DATA_8);
		break;
	default:
		break;
	}
}

void GNovatech425A::setNewStopBits()
{
	m_StopIndex = m_SettingsWidget.ui.stopBox->currentIndex();
	switch(m_StopIndex.IntValue())
	{
	case 0:
		m_pExtSerialPort->setStopBits(STOP_1);
		break;
	case 1:
		m_pExtSerialPort->setStopBits(STOP_1_5);
		break;
	case 2:
		m_pExtSerialPort->setStopBits(STOP_2);
		break;
	default:
		break;
	}
}




void GNovatech425A::ResetNovaTech()
{
	//qDebug() << "ResetNovaTech";
	if(m_pExtSerialPort)
	{
		m_pExtSerialPort->write("R\n");
		emit StatusUpdate("RESET");
	}
	else
	{
		emit StatusUpdate("No command sent - there's no m_pExtSerialPort yet!");
	}
	m_SetExtRef = 1;
}



void GNovatech425A::SetClockSource(bool clockSource)
{
	//qDebug() << "Set clock source:";
	if(m_pExtSerialPort)
	{
		if(clockSource)
		{
			m_pExtSerialPort->write("C I\n");
			emit StatusUpdate("Setting clock to Internal...\n");
			SetNovaTechFreq0(m_FreqSine);//Fix the fact that the frequency will change when the clock source changes
		}
		else
		{
			m_pExtSerialPort->write("C R\n");
			emit StatusUpdate("Setting clock to External (10 MHz)...\n");
			SetNovaTechFreq0(m_FreqSine);//Fix the fact that the frequency will change when the clock source changes
		}

	}
	else
	{
		emit StatusUpdate("No command sent - there's no m_pExtSerialPort yet!");
	}
}






void GNovatech425A::ShowPortSettings()
{
	//qDebug() << "ShowPortSettings";
	m_SettingsWidget.show();
}


void GNovatech425A::PortListCall()
{
	//qDebug() << "PortListCall";
	PortList();

}


void GNovatech425A::QueryCurrentSettings()
{
	m_DisplaySettings=1;
	//qDebug() << "QueryCurrentSettings";
	emit LEDisRed();
	m_pExtSerialPort->write("QUE\n");
}

void GNovatech425A::ReadCurrentSettings(QByteArray settings)
{
	QByteArray freqSineSettings, clockSourceSettings;
	int longLongNumDigits;
	long long freqSineLongLong;//Must be (long long) because output is a 48 bit number!
	//long double freqSineDOUBLE;
	QString totalFreqSettings,freqSineLongLongString,totalClockSourceSettings;
	bool ok;

	freqSineSettings = settings.mid(5, 12);
	clockSourceSettings = settings.mid(37,4);

	freqSineLongLong = freqSineSettings.toLongLong(&ok, 16);
	freqSineLongLong = freqSineLongLong/3;//For some reason Novatech scales the output by 3 from the input value...
	
	if(m_SetExtRef==1)
	{
		freqSineLongLongString = QString::number(freqSineLongLong, 10);
	}
	else
	{
		freqSineLongLong = freqSineLongLong/0.998138215286;
		freqSineLongLongString = QString::number(freqSineLongLong, 10);
	}

	longLongNumDigits = freqSineLongLongString.size();
	freqSineLongLongString.insert(longLongNumDigits-11,QString("."));
	freqSineLongLongString.insert(longLongNumDigits-7,QString(" "));
	freqSineLongLongString.insert(longLongNumDigits-3,QString(" "));
	freqSineLongLongString.insert(longLongNumDigits+1,QString(" "));
	totalFreqSettings = totalFreqSettings.append("FreqSine: ");
	totalFreqSettings = totalFreqSettings.append(freqSineLongLongString);
	totalFreqSettings = totalFreqSettings.append(" MHz");
	
	switch(clockSourceSettings.toInt(&ok, 10))
	{
	case 2101:
		totalClockSourceSettings = totalClockSourceSettings.append("Clock source is locked to INTERNAL.\n");
		ClockLEDisGreen();
		if (m_DisplaySettings==1)
		{
			emit StatusUpdate(totalFreqSettings);
			emit StatusUpdate(totalClockSourceSettings);
		}
		break;
	case 2108:
		totalClockSourceSettings = totalClockSourceSettings.append("Clock source FAILED to lock to external 10 MHz.\n");
		ClockLEDisRed();
		if (m_DisplaySettings==1)
		{
			emit StatusUpdate(totalFreqSettings);
			emit StatusUpdate(totalClockSourceSettings);
		}
		break;
	case 2109:
		totalClockSourceSettings = totalClockSourceSettings.append("Clock source is locked to EXTERNAL (10 MHz).\n");
		ClockLEDisGreen();
		if (m_DisplaySettings==1)
		{
			emit StatusUpdate(totalFreqSettings);
			emit StatusUpdate(totalClockSourceSettings);
		}
		break;
	default:
		totalClockSourceSettings = totalClockSourceSettings.append("Error reading clock source!\n");
		if (m_DisplaySettings==1)
		{
			emit StatusUpdate(totalFreqSettings);
			emit StatusUpdate(totalClockSourceSettings);
		}
		break;
	}

	m_DisplaySettings=0;

	m_pExtSerialPort->flush();
	
}


void GNovatech425A::SetNovaTechFreq0(double freqSine)
{
	m_pExtSerialPort->write("QUE\n");//Check to see whether external clock is locked whenever setting frequency...
	m_CurrentStatus.chop(m_CurrentStatus.length()+5);//Avoid outputting frequency by erasing m_CurrentStatus here...
	emit LEDisRed();
	QString qFreq0;
	
	if(m_SetExtRef==1)//If the clock is INTERNAL, we don't need to do any special conversion...
	{
		qFreq0 = qFreq0.number(freqSine, 'g', 14);
	}
	else//We will perform the same conversion whether or not the NOVATECH is locked or unlocked to the external
	{//clock.  If it's unlocked, you know not to trust the outputted frequency anyway...
		freqSine = freqSine*0.998138215286;//This factor comes from the manual (page 5)
		qFreq0 = qFreq0.number(freqSine, 'g', 14);
	}

	qFreq0 = qFreq0.prepend("f0 ");
	qFreq0 = qFreq0.append("\n");
	QByteArray qFreq0Array = qFreq0.toUtf8();
	char * charqFreq0 = qFreq0Array.data();
	//m_pExtSerialPort->write("CLR\n");
	m_pExtSerialPort->write(charqFreq0);
}



void GNovatech425A::SetPortName(QString portName)
{
	//qDebug() << "SetPortName";
	m_PortName = portName;

	//ConnectToPort();
	//m_pExtSerialPort->close();
	//m_pExtSerialPort->setPortName(m_PortName);
	//m_pExtSerialPort->flush();//Testing, hoping this cleans the data stored in the device.
	//m_Bytes = "";
}

QString GNovatech425A::ReturnPortName()
{
	//qDebug() << "ReturnPortName";
	return m_SetComPort.StringValue();
}

void GNovatech425A::onReadyRead()
{
	emit LEDisGreen();
	QByteArray bytes;
	int QLocation = -1;
	int a = m_pExtSerialPort->bytesAvailable();
	m_Bytes.chop(m_Bytes.length()+100);//This will initialize m_Bytes to an empty array
	//m_Bytes.resize(a);
	m_Bytes = m_pExtSerialPort->readAll();//used to be "read"

	QLocation = m_Bytes.indexOf("Q");
	//qDebug()<<"the q location "<<QLocation;
	if(QLocation > -1)//|| stillBuilding)
	{
		m_CurrentStatus = m_Bytes.right(m_Bytes.length() - QLocation);
		//m_CurrentStatus = m_Bytes;
	}
	else
	{
		if(m_CurrentStatus.contains("Q"))
		{
			m_CurrentStatus = m_CurrentStatus.append(m_Bytes);
			if (m_CurrentStatus.length() >= 45)//...until the matrix is fully built-up  This matrix
				//contains the frequency information.  THIS NUMBER (38) IS SPECIFIC TO NOVATECH MODEL AND OUTPUT FORMAT!
			{
				ReadCurrentSettings(m_CurrentStatus);
				//qDebug()<<"****Current Status: \n"<<m_CurrentStatus;
				m_CurrentStatus.chop(m_CurrentStatus.length()+5);
				m_pExtSerialPort->flush();
				//stillBuilding = false;
				//QLocation=-1;
			}
		}

	}
}

void GNovatech425A::onDsrChanged(bool status)
{
	if(status)
		qDebug() << "Novatech 425A was turned on";
	else
		qDebug() << "Novatech 425A was turned off";
}

QStringList GNovatech425A::PortList()
{
	QStringList listToReturn;
	QString statusInfo="";
	// test that displays the list of serial ports
	QList<QextPortInfo> ports = QextSerialEnumerator::getPorts();
	//qDebug() << "List of serial ports:";
	for (int i = 0; i < ports.size(); i++) 
	{
		QString portStr = ports.at(i).portName;
		listToReturn << portStr;
		/*qDebug() << "m_pExtSerialPort name:" << portStr;
		qDebug() << "friendly name:" << ports.at(i).friendName;
		qDebug() << "physical name:" << ports.at(i).physName;
		qDebug() << "enumerator name:" << ports.at(i).enumName;
		qDebug() <<  "vendor ID:" << QString::number(ports.at(i).vendorID, 16);
		qDebug() << "product ID:" << QString::number(ports.at(i).productID, 16);
		qDebug() << "===================================";*/

		statusInfo = statusInfo.append(ports.at(i).portName);
		statusInfo = statusInfo.prepend("m_pExtSerialPort name: ");
		statusInfo = statusInfo.append("\n");
		statusInfo = statusInfo.append("friendly name: ");
		statusInfo = statusInfo.append(ports.at(i).friendName);
		statusInfo = statusInfo.append("\n");
		statusInfo = statusInfo.append("physical name: ");
		statusInfo = statusInfo.append(ports.at(i).physName);
		statusInfo = statusInfo.append("\n");
		statusInfo = statusInfo.append("enumerator name: ");
		statusInfo = statusInfo.append(ports.at(i).enumName);
		statusInfo = statusInfo.append("\n");
		statusInfo = statusInfo.append("vendor ID: ");
		statusInfo = statusInfo.append(QString::number(ports.at(i).vendorID, 16));
		statusInfo = statusInfo.append("\n");
		statusInfo = statusInfo.append("product ID: ");
		statusInfo = statusInfo.append(QString::number(ports.at(i).productID, 16));
		statusInfo = statusInfo.append("\n");
		statusInfo = statusInfo.append("===================================");

		emit StatusUpdate(statusInfo);
		statusInfo="";

	}
	StatusUpdate("*** *** *** *** *** *** *** *** ***");
	return listToReturn;
}
