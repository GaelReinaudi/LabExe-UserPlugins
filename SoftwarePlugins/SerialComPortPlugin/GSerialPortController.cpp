#include "GSerialPortController.h"
#include "GSerialPortControllerWidget.h"
#include "qExtSerialPort/src/qextserialport.h"
#include "qExtSerialPort/src/qextserialenumerator.h"
#include <stdio.h>
#include <QMutexLocker>
#include "hled.h"

//Needed for "OnDataAvailable"

//^Needed for "OnDataAvailable"

GSerialPortController::GSerialPortController(QObject *parent, QString uniqueIdentifierName /* = "" */)
	: GProgDevice(parent, uniqueIdentifierName)
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
	, m_ComPortSettings("Com Port Settings", this)
	, m_Reset("Reset NovaTech", this)
	, m_Freq0("Freq 0:", this)
	, m_Freq1("Freq 1:", this)
	, m_Freq2("Freq 2:", this)
	, m_Freq3("Freq 3:", this)
	, m_ListPorts("List Available Ports", this)

	, m_FirstTime("First Time", this)



	
{

	// is this the shelved instance of the device
	if(IsShelvedInstance())	
	{

	}
	else 
	{

	}
	m_pExtSerialPort = new QextSerialPort(QextSerialPort::EventDriven);
	
	
}

void GSerialPortController::PopulateDeviceWidget(GDeviceWidget* theDeviceWidget )
{
 	QWidget* pWid = new GSerialPortControllerWidget(this, theDeviceWidget);
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

GSerialPortController::~GSerialPortController()
{

}


void GSerialPortController::LatterInitialization()
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
	connect(&m_ComPortSettings, SIGNAL(ValueUpdated(bool)), this, SLOT(ShowPortSettings()));
	

	//Com Port Settings buttons...
	connect(m_SettingsWidget.ui.baudBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setNewBaudRate()));
	connect(m_SettingsWidget.ui.flowBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setNewFlowControl()));
	connect(m_SettingsWidget.ui.parityBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setNewParity()));
	connect(m_SettingsWidget.ui.dataBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setNewDataBits()));
	connect(m_SettingsWidget.ui.stopBox, SIGNAL(currentIndexChanged(int)), this, SLOT(setNewStopBits()));

	

	//ConnectToPort();
}

void GSerialPortController::ConnectToPort()

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




	connect(&m_Freq0, SIGNAL(ValueUpdated(double)), this, SLOT(SetNovaTechFreq0(double)));
	connect(&m_Freq1, SIGNAL(ValueUpdated(double)), this, SLOT(SetNovaTechFreq1(double)));
	connect(&m_Freq2, SIGNAL(ValueUpdated(double)), this, SLOT(SetNovaTechFreq2(double)));
	connect(&m_Freq3, SIGNAL(ValueUpdated(double)), this, SLOT(SetNovaTechFreq3(double)));
	connect(&m_Settings, SIGNAL(ValueUpdated(bool)), this, SLOT(QueryCurrentSettings()));




}


void GSerialPortController::setNewFlowControl()
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


void GSerialPortController::setNewBaudRate()
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

void GSerialPortController::setNewParity()
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

void GSerialPortController::setNewDataBits()
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

void GSerialPortController::setNewStopBits()
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




void GSerialPortController::ResetNovaTech()
{
	if(m_pExtSerialPort)
	{
		m_pExtSerialPort->write("R\n");
		emit StatusUpdate("RESET");
	}
	else
	{
		emit StatusUpdate("No command sent - there's no m_pExtSerialPort yet!");
	}
}

void GSerialPortController::ShowPortSettings()
{
	m_SettingsWidget.show();
}


void GSerialPortController::PortListCall()
{
	PortList();

}


void GSerialPortController::QueryCurrentSettings()
{
	emit LEDisRed();
	m_pExtSerialPort->write("QUE\n");
}

void GSerialPortController::ReadCurrentSettings(QByteArray settings)
{
	QByteArray freq0Settings, freq1Settings, freq2Settings, freq3Settings;
	int freq0INT, freq1INT, freq2INT, freq3INT;
	double freq0DOUBLE, freq1DOUBLE, freq2DOUBLE, freq3DOUBLE;
	QString totalFreqSettings;
	qDebug()<<settings;
	freq0Settings = settings.mid(5, 8);
	freq1Settings = settings.mid(55, 8);
	freq2Settings = settings.mid(105, 8);
	freq3Settings = settings.mid(155, 8);

	freq0Settings = freq0Settings.toLower();
	freq1Settings = freq1Settings.toLower();
	freq2Settings = freq2Settings.toLower();
	freq3Settings = freq3Settings.toLower();

	freq0INT = freq0Settings.toInt(0,16);
	freq1INT = freq1Settings.toInt(0,16);
	freq2INT = freq2Settings.toInt(0,16);
	freq3INT = freq3Settings.toInt(0,16);

	freq0DOUBLE = double(freq0INT)/10000000;
	freq1DOUBLE = double(freq1INT)/10000000;
	freq2DOUBLE = double(freq2INT)/10000000;
	freq3DOUBLE = double(freq3INT)/10000000;

	totalFreqSettings = totalFreqSettings.append("Freq 0: ");
	totalFreqSettings = totalFreqSettings.append(QString::number(freq0DOUBLE, 'f', 7));
	totalFreqSettings = totalFreqSettings.append("\n");
	totalFreqSettings = totalFreqSettings.append("Freq 1: ");
	totalFreqSettings = totalFreqSettings.append(QString::number(freq1DOUBLE, 'f', 7));
	totalFreqSettings = totalFreqSettings.append("\n");
	totalFreqSettings = totalFreqSettings.append("Freq 2: ");
	totalFreqSettings = totalFreqSettings.append(QString::number(freq2DOUBLE, 'f', 7));
	totalFreqSettings = totalFreqSettings.append("\n");
	totalFreqSettings = totalFreqSettings.append("Freq 3: ");
	totalFreqSettings = totalFreqSettings.append(QString::number(freq3DOUBLE, 'f', 7));
	totalFreqSettings = totalFreqSettings.append("\n");

	emit StatusUpdate(totalFreqSettings);
	//PortList();
}

void GSerialPortController::SetPortName(QString portName)
{
	m_PortName = portName;
	
	//ConnectToPort();
	//m_pExtSerialPort->close();
	//m_pExtSerialPort->setPortName(m_PortName);
	//m_pExtSerialPort->flush();//Testing, hoping this cleans the data stored in the device.
	//m_Bytes = "";
}

void GSerialPortController::SetNovaTechFreq0(double freq0)
{
	emit LEDisRed();
	QString qFreq0;
	qFreq0 = qFreq0.number(freq0, 'g', 10);
	qFreq0 = qFreq0.prepend("f0 ");
	qFreq0 = qFreq0.append("\n");
	QByteArray qFreq0Array = qFreq0.toUtf8();
	char * charqFreq0 = qFreq0Array.data();
	//m_pExtSerialPort->write("CLR\n");
	m_pExtSerialPort->write(charqFreq0);
}

void GSerialPortController::SetNovaTechFreq1(double freq1)
{
	emit LEDisRed();
	QString qFreq1;
	qFreq1 = qFreq1.number(freq1, 'g', 10);
	qFreq1 = qFreq1.prepend("f1 ");
	qFreq1 = qFreq1.append("\n");
	QByteArray qFreq1Array = qFreq1.toUtf8();
	char * charqFreq1 = qFreq1Array.data();
	m_pExtSerialPort->write(charqFreq1);
}

void GSerialPortController::SetNovaTechFreq2(double freq2)
{
	emit LEDisRed();
	QString qFreq2;
	qFreq2 = qFreq2.number(freq2, 'g', 10);
	qFreq2 = qFreq2.prepend("f2 ");
	qFreq2 = qFreq2.append("\n");
	QByteArray qFreq2Array = qFreq2.toUtf8();
	char * charqFreq2 = qFreq2Array.data();
	//m_pExtSerialPort->write("CLR\n");
	m_pExtSerialPort->write(charqFreq2);
}

void GSerialPortController::SetNovaTechFreq3(double freq3)
{
	emit LEDisRed();
	QString qFreq3;
	qFreq3 = qFreq3.number(freq3, 'g', 10);
	qFreq3 = qFreq3.prepend("f3 ");
	qFreq3 = qFreq3.append("\n");
	QByteArray qFreq3Array = qFreq3.toUtf8();
	char * charqFreq3 = qFreq3Array.data();
	//m_pExtSerialPort->write("CLR\n");
	m_pExtSerialPort->write(charqFreq3);
}

QString GSerialPortController::ReturnPortName()
{
	return m_SetComPort.StringValue();
}


//void GSerialPortController::OnDataAvailable() 
//{
//	QextSerialPort* port = new QextSerialPort(m_PortName, QextSerialPort::EventDriven);
//	connect(port, SIGNAL(readyRead()), this, SLOT(onDataAvailable()));
//	port->open(0);
//    int avail = port->bytesAvailable();
//    if( avail > 0 ) 
//	{
//        QByteArray usbdata;
//        usbdata.resize(avail);
//        int read = port->read(usbdata.data(), usbdata.size());
//        if( read > 0 ) 
//		{
//            //processNewData(usbdata);
//        }
//    }
//}

void GSerialPortController::onReadyRead()
{
	emit LEDisGreen();
	QByteArray bytes;
	int QLocation = -1;
//	int a = m_pExtSerialPort->bytesAvailable();
	m_Bytes.chop(m_Bytes.length()+100);//This will initialize m_Bytes to an empty array
	//m_Bytes.resize(a);
	m_Bytes = m_pExtSerialPort->readAll();//used to be "read"
	//qDebug() << "bytes read:" << m_Bytes.size();
	//qDebug() << "bytes:" << m_Bytes;

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
			//qDebug()<<"M_CurrentStatus while building: "<<m_CurrentStatus;
			if (m_CurrentStatus.length() >= 200)//...until the matrix is fully built-up  This matrix
				//contains the frequency information.
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
	//else
	//{
	//	//m_CurrentStatus = bytes;
	//	m_CurrentStatus = m_Bytes;
	//}
	//m_pExtSerialPort->read(m_Bytes.data(), m_Bytes.size());//hopefully this will give a little time...

}

void GSerialPortController::onDsrChanged(bool status)
{
	if(status)
		qDebug() << "device was turned on";
	else
		qDebug() << "device was turned off";
}

QStringList GSerialPortController::PortList()
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

/////////////////////////////////////////////////////////////////////
/*!
Detailed descrption.
\return: void : 
*////////////////////////////////////////////////////////////////////
//void GSerialPortController::ConnectToPort()
//{
//	qDebug() << "GSerialPortController::ConnectToPort";
//}

//void GSerialPortController::WriteToNovaTech()
//{
//	m_pExtSerialPort->write
