#include "GMenloDDS120.h"
#include "GMenloDDS120Widget.h"
#include <stdio.h>
#include <QMutexLocker>
#include "hled.h"

//Needed for "OnDataAvailable"

//^Needed for "OnDataAvailable"

GMenloDDS120::GMenloDDS120(QString uniqueIdentifierName, QObject *parent)
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

	, m_Settings("Get Frequency", this)
	, m_DisplaySettings("This name won't show up...", this)
	, m_ComPortSettings("Com Port Settings", this)
	, m_Reset("Serial Control Offline", this)
	, m_FreqSine("DDS120 Freq. (Hz):", this)
	, m_ListPorts("List Available Serial Ports", this)
	, m_FirstTime("First Time", this)
	, m_PortStatus("Port status", this)
	, m_SetExtRef("Clock source", this)	
{
	m_pExtSerialPort = new QextSerialPort(QextSerialPort::EventDriven);
	
	//! [Extra initialization of the parameters]
	m_FreqSine.SetHardLimits(0.0,120000000.0);//! 0-120 MHz
	m_FreqSine.SetTypicalStep(0.00001);
	m_FreqSine.SetDisplayDecimals(5);
	//m_FreqSine.SetParamValue(20000000);//! 20 MHz (not working?)
	//m_PortName = "COM14";
	m_PortStatus = -1;
}

void GMenloDDS120::PopulateDeviceWidget(GDeviceWidget* theDeviceWidget )
{
 	QWidget* pWid = new GMenloDDS120Widget(this, theDeviceWidget);
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

	//Connect actions to set or get the frequency. (do this here to avoid multiple function calls if reopen serial port...)
	connect(&m_FreqSine, SIGNAL(ValueUpdated(double)), this, SLOT(SetNovaTechFreq0(double)));
	connect(&m_Settings, SIGNAL(ValueUpdated(bool)), this, SLOT(GetFrequency()));
}

GMenloDDS120::~GMenloDDS120()
{

}


void GMenloDDS120::LatterInitialization()
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
	//connect(&m_Reset, SIGNAL(ValueUpdated(bool)), this, SLOT(ResetNovaTech()));
	//connect(&m_SetExtRef, SIGNAL(ValueUpdated(bool)), this, SLOT(SetClockSource(bool)));
	//connect(&m_ComPortSettings, SIGNAL(ValueUpdated(bool)), this, SLOT(ShowPortSettings()));
	

	//Com Port Settings buttons...
	connect(m_SettingsWidget.ui.baudBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setNewBaudRate()));
	connect(m_SettingsWidget.ui.flowBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setNewFlowControl()));
	connect(m_SettingsWidget.ui.parityBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setNewParity()));
	connect(m_SettingsWidget.ui.dataBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setNewDataBits()));
	connect(m_SettingsWidget.ui.stopBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setNewStopBits()));

	//SetClockSource(m_SetExtRef);
	//ClockLEDisGreen();//MICKEY (2016-02-12): Should start out green, light will only turn red when frequency is 
                      //incremented or Novatech 425A settings are queried.
	m_DisplaySettings = 0;

	//ConnectToPort();
}

void GMenloDDS120::ConnectToPort()
{	// Prevent multiple ports being open: 
	if(m_pExtSerialPort)
	{	//emit StatusUpdate("Closing port...\n"); 
		LEDisRed();
		//m_pExtSerialPort->flush();
		//m_pExtSerialPort->reset();
		m_pExtSerialPort->close();
		disconnect(m_pExtSerialPort);
		//disconnect(&m_FreqSine);
		//disconnect(&m_Settings);

		emit StatusUpdate("Opening port...\n"); 
		delete m_pExtSerialPort;
		m_pExtSerialPort = new QextSerialPort(QextSerialPort::EventDriven);
		
	}
	
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
			emit StatusUpdate("warning: DDS120 is not turned on");
		}
		emit StatusUpdate("listening for data on "+m_pExtSerialPort->portName());
		emit LEDisGreen();

		//Serial port settings for Menlo Systems DDS120 synthesizer (email 2/5/2016 from Menlo to Bart):
		m_pExtSerialPort->setBaudRate(BAUD115200);
		m_pExtSerialPort->setFlowControl(FLOW_OFF);
		m_pExtSerialPort->setParity(PAR_NONE);
		m_pExtSerialPort->setDataBits(DATA_8);
		m_pExtSerialPort->setStopBits(STOP_1);


		//Connect actions to set or get the frequency. DON'T DO THIS HERE because leads to multiple function calls is reopen serial port. 
		//connect(&m_FreqSine, SIGNAL(ValueUpdated(double)), this, SLOT(SetNovaTechFreq0(double)));
		//connect(&m_Settings, SIGNAL(ValueUpdated(bool)), this, SLOT(GetFrequency()));

		//The frequency comb can't tolerate huge changes in the DDS120 frequency, so 
		//since the serial port has just opened, it'd be nice to grab what the frequency 
		//is and to update m_FreqSine with that value.  
		//GetFrequency();
		//Huh, weird! Think LabExe automatically triggers a GetFrequency() at startup by setting the button's value, 
		// so don't need to retrigger it here. 
		//Well, this works now -- the frequency in LabExe is set to the DDS120's current value when LabExe starts. 
		//(Because of onreadyread() flow control.) 
	}
	else 
	{
		emit StatusUpdate("GMenloDDS120 device failed to open:"+m_pExtSerialPort->errorString());
	}
}

void GMenloDDS120::setNewFlowControl()
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


void GMenloDDS120::setNewBaudRate()
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

void GMenloDDS120::setNewParity()
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

void GMenloDDS120::setNewDataBits()
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

void GMenloDDS120::setNewStopBits()
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




// void GMenloDDS120::ResetNovaTech()
// {
// 	qDebug() << "ResetNovaTech";
//	// not used for DDS120
// }
// 
// 
// 
// void GMenloDDS120::SetClockSource(bool clockSource)
// {
// 	qDebug() << "Set clock source:";
//	// not used for DDS120
// }

void GMenloDDS120::ShowPortSettings()
{
	//qDebug() << "ShowPortSettings";
	m_SettingsWidget.show();
}


void GMenloDDS120::PortListCall()
{
	//qDebug() << "PortListCall";
	PortList();

}


void GMenloDDS120::GetFrequency()
{
	m_DisplaySettings=1;
	//qDebug() << "GetFrequency...";

	emit LEDisRed();//onReadyRead() will make green if command is successful
	
	//Test if serial port is open...
	if(m_pExtSerialPort->lineStatus()!=0)
	{	//qDebug() << "GetFrequency OK";
		m_pExtSerialPort->write("GF");
		//The DDS120 responds, which is captured and processed by onReadyRead() below.
	}
	else
	{	//qDebug() << "GetFrequency will NOT send command";

	}
}

// void GMenloDDS120::ReadCurrentSettings(QByteArray settings)
// {
// 	// not used for DDS120
// 	
// }


void GMenloDDS120::SetNovaTechFreq0(double freqSine)
{	emit LEDisRed();//onReadyRead() will make green if command is successful
	
	if(m_pExtSerialPort->lineStatus()!=0)
	{	// serial port is open
		if((freqSine >=0)&&(freqSine <=120000000))//Within range?
		{
			QString qFreq0;
			qFreq0 = qFreq0.number(freqSine*100000, 'f', 0);//units uHz, no decimals
			qFreq0.prepend("00000000000000");//add zeros to front (missing from previous operation)
			qFreq0.remove(0,qFreq0.length()-14);//truncate front zeros until size is 14 characters.
			qFreq0.prepend("SF");
			qFreq0.append("");
			//qDebug() << "Writing to DDS120: "<<qFreq0;
			QByteArray qFreq0Array = qFreq0.toUtf8();
			char * charqFreq0 = qFreq0Array.data();
			m_pExtSerialPort->write(charqFreq0);
		}
		else
		{
			qDebug() << "WARNING for DDS120: Trying to set frequency outside of range!\n";
			emit LEDisRed();
		}
	}
	else
	{	//qDebug() << "Can't set frequency because port not open to DDS120";

	}
}



void GMenloDDS120::SetPortName(QString portName)
{
	//qDebug() << "SetPortName";
	m_PortName = portName;
}

QString GMenloDDS120::ReturnPortName()
{
	//qDebug() << "ReturnPortName";
	return m_SetComPort.StringValue();
}

void GMenloDDS120::onReadyRead()
{
	emit LEDisGreen();
	QByteArray bytes;
	int QLocation = -1;
	int a = m_pExtSerialPort->bytesAvailable();
	m_Bytes.chop(m_Bytes.length()+100);//This will initialize m_Bytes to an empty array
	m_Bytes = m_pExtSerialPort->readAll();//used to be "read"
	//qDebug() << "DDS120 says:\n" << m_Bytes;
	
	//Test if captured single, full message from DDS120
	if(m_Bytes.startsWith("")&&m_Bytes.endsWith("")&&(m_Bytes.count("")==1)&&(m_Bytes.count("")==1))
	{	//Message should be OK. DDS120 always starts with SOH and ends with ETX characters. Any duplication of those characters means an error too. 

		if(m_Bytes.contains("OK"))
		{	//Success! 
			//qDebug()<<"Congrats! DDS120 accepted your command.\n";
		}
		else if(m_Bytes.contains("E0"))
		{	emit StatusUpdate("ERROR: Command not accepted!\n");
		}
		else if(m_Bytes.contains("E1"))
		{	emit StatusUpdate("ERROR: Setting value out of range!\n");
		}
		else
		{	//Everything else goes here. 

			//Assume this is response to GetFrequency() (nothing else is programmed...): 
			m_Bytes.remove(0,1);//remove start of line
			m_Bytes.chop(1);//remove end of line
			//qDebug()<<m_Bytes.toDouble();//units uHz.
			
			//update m_FreqSine with new value:
			//warning -- this triggers a set command, but that's not too much extra computer work. 
			//It doesn't create an infinite loop because the set command doesn't trigger GetFrequency() again.  
			m_FreqSine.SetParamValue(m_Bytes.toDouble()/100000);//units Hz

			//instead display as status update, following the Novatech Plugins that this code copies: 
			QString temp;
			temp = temp.number(m_FreqSine.DoubleValue(),'f',5);//units Hz
			emit StatusUpdate(temp+" Hz.");
		}
	}
	else
	{	//Message is incomplete or bad.
		qDebug()<<"Bad or incomplete message from DDS120.\n";
	}

	m_DisplaySettings=0;
	m_pExtSerialPort->flush();

// 	QLocation = m_Bytes.indexOf("Q");
// 	//qDebug()<<"the q location "<<QLocation;
// 	if(QLocation > -1)//|| stillBuilding)
// 	{
// 		m_CurrentStatus = m_Bytes.right(m_Bytes.length() - QLocation);
// 		//m_CurrentStatus = m_Bytes;
// 	}
// 	else
// 	{
// 		if(m_CurrentStatus.contains("Q"))
// 		{
// 			m_CurrentStatus = m_CurrentStatus.append(m_Bytes);
// 			if (m_CurrentStatus.length() >= 45)//...until the matrix is fully built-up  This matrix
// 				//contains the frequency information.  THIS NUMBER (38) IS SPECIFIC TO NOVATECH MODEL AND OUTPUT FORMAT!
// 			{
// 				ReadCurrentSettings(m_CurrentStatus);
// 				//qDebug()<<"****Current Status: \n"<<m_CurrentStatus;
// 				m_CurrentStatus.chop(m_CurrentStatus.length()+5);
// 				m_pExtSerialPort->flush();
// 				//stillBuilding = false;
// 				//QLocation=-1;
// 			}
// 		}
// 
// 	}
}

void GMenloDDS120::onDsrChanged(bool status)
{
	if(status)
		qDebug() << "DDS120 was turned on";
	else
		qDebug() << "DDS120 was turned off";
}

QStringList GMenloDDS120::PortList()
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
