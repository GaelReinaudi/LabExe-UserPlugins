#include "GSRSController.h"
//#include <QString>
//#include <QObject>
//#include <QIODevice>
//#include <QThread>
#include "Winsock2.h" 
#pragma comment(lib,  "ws2_32.lib")

/* prototypes */ 
void init_tcpip(void); 
int sg_connect(unsigned long ip); 
int sg_close(void); 
int sg_write(char *str); 
int sg_write_bytes(const void *data, unsigned num); 
int sg_read(char *buffer, unsigned num);

//QLineEdit *IPLineEdit = new QLineEdit();

QString yes = "Yes";
QString no = "No";





SOCKET sSG384;               /* sg384 tcpip socket */ 
unsigned sg_timeout = 6000;  /* Read timeout in milliseconds */ 

int argc=2;
//const char * argv="128.59.171.142";//Should probably make this user-input at some point...
//unsigned long ip = inet_addr(argv);


//! [Initialize the parameters]
GSRSController::GSRSController(QObject *parent, QString uniqueIdentifierName /* = "" */)
: GProgDevice(parent, uniqueIdentifierName)
, m_Frequency("Frequency (MHz)", this)
, m_BabyStepSize("Baby Step Size (kHz)", this)
, m_ShiftTime("Shift Time (seconds)", this)
, m_IPAddress("IP Address", this)
, m_ModulationDev("Modulation Deviation", this)
, m_ModulationRate("Modulation Rate", this)
, m_IsConnected("Connection Successful?", this)
, m_SweepStatus("", this)
//, m_CurrentFreq("Current Frequency (Hz)", this, GPARAM::ReadOnly)
//, m_ReadFreq("Read Frequency", this)
{
	//! [Initialize the parameters]
	/*
	Note: All parameters defined with "this" device as parent (see above) will be saved automatically 
	when the device state is saved to file. The name used to save the values is the same as the one provided 
	for the name (the first argument, e.g. "num. samples").
	*/
	//! [Extra initialization the parameters]
	// Default value of the sample size for the first use.
	// It will be over-written if a previously saved value is read from a file.
	
	init_tcpip(); //initialize the sockets library
	//m_SgIsConnected = sg_connect( inet_addr(argv));//This will be used in if-statements later on,
	m_SgIsConnected = 0;
	//to check if it's okay to send commands.
//	connect (&m_ReadFreq, SIGNAL(ValueUpdated()), this, SLOT(
	//connect(IPLineEdit, SIGNAL(editingFinished()), this, SLOT(SetIPAddress()));
	connect(&m_IPAddress, SIGNAL(ValueUpdated(QString)), this, SLOT(SetIPAddress(QString)));
	connect(&m_Frequency, SIGNAL(ValueUpdated(double)), this, SLOT(SetFrequencyStart(double)));
	connect(&m_ModulationDev, SIGNAL(ValueUpdated(double)), this, SLOT(SetModulationDev(double)));
	connect(&m_ModulationRate, SIGNAL(ValueUpdated(double)), this, SLOT(SetModulationRate(double)));
	connect(&m_SweepStatus, SIGNAL(ValueUpdated(bool)), this, SLOT(SetSweepStatus(bool)));
}

//! [Extra initialization the parameters]

GSRSController::~GSRSController()
{
	
}

/////////////////////////////////////////////////////////////////////
/*!
Populates a widget provided by a workbench in order to represent (and be adequately connected to) this GSRSController. 
Layouts are used to make the widget react correctly to re-sizing.
The easiest way to connect the button and spinboxes to the actual instance of the corresponding parameter 
is to use the method GParamXXXX::ProvideNew----Widget(), that does all the necessary connections 
automatically (which would be the equivalent of this PopulateDeviceWidget(), but for a single parameter).
\param:  GDeviceWidget * theDeviceWidget : the parent widget in the gui.
*////////////////////////////////////////////////////////////////////
//[PopulateDeviceWidgetImplementation]
void GSRSController::PopulateDeviceWidget(GDeviceWidget* theDeviceWidget )
{


	//QLineEdit *IPLineEdit = new QLineEdit();
	//IPLineEdit->setInputMask("000.000.000.000");
	//IPLineEdit->setText("128.59.171.142");
	// We add a vertical layout to hold together all the widgets that we are going to display.
	QVBoxLayout* pVlay = new QVBoxLayout();
	theDeviceWidget->AddSubLayout(pVlay);
	// We add a form layout that will hold the numerical settings.
	QFormLayout* pFLay = new QFormLayout();
	pVlay->addLayout(pFLay);
	pFLay->addRow(m_Frequency.ProvideNewLabel(theDeviceWidget), m_Frequency.ProvideNewParamSpinBox(theDeviceWidget));
	//pFLay->addRow(m_ShiftTime.ProvideNewLabel(theDeviceWidget), m_ShiftTime.ProvideNewParamSpinBox(theDeviceWidget));
	//pFLay->addRow(m_BabyStepSize.ProvideNewLabel(theDeviceWidget), m_BabyStepSize.ProvideNewParamSpinBox(theDeviceWidget));
	pFLay->addRow(m_ModulationDev.ProvideNewLabel(theDeviceWidget), m_ModulationDev.ProvideNewParamSpinBox(theDeviceWidget));
	pFLay->addRow(m_ModulationRate.ProvideNewLabel(theDeviceWidget), m_ModulationRate.ProvideNewParamSpinBox(theDeviceWidget));
	
	//pFLay->addRow(m_CurrentFreq.ProvideNewLabel(theDeviceWidget), m_CurrentFreq.ProvideNewParamSpinBox(theDeviceWidget));
	pFLay->addRow(m_IPAddress.ProvideNewLabel(theDeviceWidget), m_IPAddress.ProvideNewParamLineEdit(theDeviceWidget));
	
	// We add an expandable space.
	//pFLay->addRow(tr("&IP Address:"), IPLineEdit);
	//pFLay->addRow(m_IPAddress.ProvideNewLabel(theDeviceWidget), m_IPAddress.ProvideNewParamLineEdit(theDeviceWidget));
	pFLay->addRow(m_IsConnected.ProvideNewLabel(theDeviceWidget), m_IsConnected.ProvideNewParamRadioButtons(theDeviceWidget, "Yes", "No"));
	pFLay->addRow(tr("&Enable Sweep:"), m_SweepStatus.ProvideNewParamCheckBox(theDeviceWidget));

	pVlay->addStretch();
	//connect(IPLineEdit, SIGNAL(textEdited(QString)), this, SLOT(SetIPAddressCopy(QString)));
	//connect(IPLineEdit, SIGNAL(editingFinished()), this, SLOT(SetIPAddress()));

	
	
}
void GSRSController::SetIPAddress(QString ip)
{
	QByteArray qIPArray = ip.toUtf8();
	const char * ipChar = qIPArray.data();
	m_SgIsConnected = sg_connect( inet_addr(ipChar));
	if(m_SgIsConnected == 1)
	{
		m_IsConnected = true;
	}
	else
	{
		m_IsConnected = false;
	}
}




void GSRSController::SetModulationDev(double modDev)
{
	QString qModDev;
	qModDev = qModDev.number(modDev, 'g', 15);
	qModDev = qModDev.prepend("SDEV ");
	qModDev = qModDev.append(" MHz\n");
	QByteArray qModDevArray = qModDev.toUtf8();
	char * charqModDev = qModDevArray.data();
	sg_write(charqModDev);
	sg_write("LCAL\n");
}

void GSRSController::SetModulationRate(double modRate)
{
	QString qModRate;
	qModRate = qModRate.number(modRate, 'g', 15);
	qModRate = qModRate.prepend("SRAT ");
	qModRate = qModRate.append("\n");
	QByteArray qModRateArray = qModRate.toUtf8();
	char * charqModRate = qModRateArray.data();
	sg_write(charqModRate);
	sg_write("LCAL\n");
}

void GSRSController::SetSweepStatus(bool sweeponoff)
{
	if(sweeponoff)
	{
		sg_write("MFNC 1\n");//"1" indicates we're sweeping with a ramp function, "2" means triangle.
		sg_write("MODL 1\n");
		sg_write("LCAL\n");
	}
	else
	{
		sg_write("MODL 0\n");
		sg_write("LCAL\n");
	}
}


void GSRSController::SetFrequencyStart(double freq)
{
	/*QDialogButtonBox buttonBox;
	buttonBox.addButton(findButton, QDialogButtonBox::ActionRole);*/
	
	double modRate, modDev, shiftTime = m_ShiftTime.DoubleValue();

	modDev = abs(freq - m_PrevFreq);
	QString qFreq, qModRate, qPrevFreq, qModDev, lc1="LSTP 0, ", lc2="LSTP 1, ";//lc1 and lc2 are list commands
	if (freq != 0)
	{
		qFreq = qFreq.number(freq,'g',15);
	}
	else
	{
		qFreq = qFreq.number(888.888, 'g', 15);//This is just to avoid an error the first time you run the program.
	}
	qPrevFreq = qPrevFreq.number(m_PrevFreq,'g',15);
	qModDev = qModDev.number(modDev,'g',15);
	if (m_BabyStepSize.DoubleValue() != 0)//Inputting a BabyStepSize overrides the sweep time
	{
		if (m_PrevFreq<freq)//If you're babystepping up...
		{
			while (m_PrevFreq+m_BabyStepSize/1000.0<freq)
			{
				m_PrevFreq += m_BabyStepSize.DoubleValue()/1000.0;
				qFreq = qFreq.number(m_PrevFreq,'g',15);
				qFreq=qFreq.prepend("FREQ ");
				qFreq=qFreq.append(" MHz\n");
				QByteArray qFreqArray = qFreq.toUtf8();
				char * charqFreq = qFreqArray.data();
				sg_write(charqFreq);
				//sleep(1);
			}
		}
		else//If you're babystepping down...
		{
			while (m_PrevFreq-m_BabyStepSize/1000.0>freq)
			{
				m_PrevFreq -= m_BabyStepSize.DoubleValue()/1000.0;
				qFreq = qFreq.number(m_PrevFreq,'g',15);
				qFreq=qFreq.prepend("FREQ ");
				qFreq=qFreq.append(" MHz\n");
				QByteArray qFreqArray = qFreq.toUtf8();
				char * charqFreq = qFreqArray.data();
				sg_write(charqFreq);
				//sleep(1);
			}
		}
		qFreq = qFreq.number(freq,'g',15);//One last command to set the frequency to freq.
		qFreq=qFreq.prepend("FREQ ");
		qFreq=qFreq.append(" MHz\n");
		QByteArray qFreqArray = qFreq.toUtf8();
		char * charqFreq = qFreqArray.data();
		sg_write(charqFreq);
		sg_write("LCAL\n");//Set local control again.
	}
	else//if m_BabyStepSize is zero...
	{
		if (m_ShiftTime.DoubleValue() != 0)
		{
			if (freq-m_PrevFreq > 0.0)//If you're sweeping forward...
			{
				modRate = 0.25/shiftTime;
				qModRate = qModRate.number(modRate,'g',15);

				//Build first list command
				lc1.append(qPrevFreq);
				lc1.append("e6,N,N,N,N,N,1,3,0,");//The "2" in this command causes the sweep function to
				//be a triangle wave.  For sinusoidal sweep, replace 
				//with 0 (see manual).
				lc1.append(qModRate);//This is in hertz.
				lc1.append(",");
				lc1.append(qModDev);
				lc1.append("e6,N,N,N,N\n");

				//Build second list command
				lc2.append(qFreq);
				lc2.append("e6,N,N,N,N,N,0,N,N,N,N,N,N,N,N\n");

				//Turn commands into char * (so sg_write can accept them)
				QByteArray lc1Array = lc1.toUtf8();
				QByteArray lc2Array = lc2.toUtf8();
				char * charLC1 = lc1Array.data();
				char * charLC2 = lc2Array.data();

				if (m_SgIsConnected)
				{ 
					sg_write("LSTC? 2\n");//Tell the SG384 that I'm going to make a list w/ 2 commands
					sg_write(charLC1);
					sg_write(charLC2);
					sg_write("LSTE 1\n");//Enable the list.
					sg_write("*TRG\n");//Trigger the first command.
					//sg_write("*CLS\n");//This command makes the error light go away - see page 63 of SRS manual
					QTimer::singleShot(int(shiftTime*1000), this, SLOT(SetFrequencyStop()));

				}
			}
			else//If you're sweeping backward...
			{
				modRate = 245.0/(100000.0*shiftTime);//Determined empirically to work...
				qModRate = qModRate.number(modRate,'g',15);

				//Build first list command
				lc1.append(qPrevFreq);
				lc1.append("e6,N,N,N,N,N,1,3,1,");//The "3" in this command causes the sweep function
				//to ramp.  This is the only way to get the SRS to sweep backwards.
				//with 0 (see manual).
				lc1.append(qModRate);//This is in hertz.
				lc1.append(",");
				lc1.append(qModDev);
				lc1.append("e6,N,N,N,N\n");

				//Build second list command
				lc2.append(qFreq);
				lc2.append("e6,N,N,N,N,N,0,N,N,N,N,N,N,N,N\n");

				//Turn commands into char * (so sg_write can accept them)
				QByteArray lc1Array = lc1.toUtf8();
				QByteArray lc2Array = lc2.toUtf8();
				char * charLC1 = lc1Array.data();
				char * charLC2 = lc2Array.data();

				if (m_SgIsConnected)
				{ 
					sg_write("LSTC? 2\n");//Tell the SG384 that I'm going to make a list w/ 2 commands
					sg_write(charLC1);
					sg_write(charLC2);
					sg_write("LSTE 1\n");//Enable the list.
					sg_write("*TRG\n");//Trigger the first command.
					//sg_write("*CLS\n");//This command makes the error light go away - see page 63 of SRS manual
					QTimer::singleShot(int(shiftTime*1000), this, SLOT(SetFrequencyStop()));

				}
			}
		}
		else//If shiftTime *is* equal to zero, immediately set to freq
		{
			if(m_SgIsConnected)
			{ 
				qFreq=qFreq.prepend("FREQ ");
				qFreq=qFreq.append(" MHz\n");
				QByteArray qFreqArray = qFreq.toUtf8();
				char * charqFreq = qFreqArray.data();
				sg_write(charqFreq);
				sg_write("LCAL\n");
			}
		}
	}
	m_PrevFreq=freq;
}

void GSRSController::SetFrequencyStop()
{
	sg_write("*TRG\n");//Trigger the second command
	sg_write("LCAL\n");

}

int sg_connect(unsigned long ip) 
{ 
	/* Connect to the sg384 */ 
	struct sockaddr_in intrAddr; 
	int status; 

	sSG384 = socket(AF_INET,SOCK_STREAM,0); 
	if ( sSG384 == INVALID_SOCKET ) 
		return 0; 

	/* Bind to a local port */ 
	memset(&intrAddr,0,sizeof(intrAddr)); 
	intrAddr.sin_family = AF_INET; 
	intrAddr.sin_port = htons(0); 
	intrAddr.sin_addr.S_un.S_addr = htonl(INADDR_ANY); 
	if ( SOCKET_ERROR == bind(sSG384,(const struct sockaddr 
		*)&intrAddr,sizeof(intrAddr)) ) { 
			//closesocket(sSG384); 
			sSG384 = INVALID_SOCKET; 
			return 0; 
	} 
	/* Setup address for the connection to dg on port 5025 */ 
	memset(&intrAddr,0,sizeof(intrAddr)); 
	intrAddr.sin_family = AF_INET; 
	intrAddr.sin_port = htons(5025); 
	intrAddr.sin_addr.S_un.S_addr = ip; 
	status = connect(sSG384,(const struct sockaddr *)&intrAddr,sizeof(intrAddr)); 
	if ( status ) { 
		//closesocket(sSG384); 
		sSG384 = INVALID_SOCKET; 
		return 0; 
	} 
	return 1;
} 

int sg_close(void) 
{ 
	if ( closesocket(sSG384) != SOCKET_ERROR ) 
		return 1; 
	else 
		return 0;
} 

int sg_write(char * str) 
{ 
	/* Write string to connection */
	int result; 
	result = send(sSG384,str,(int)strlen(str),0);
	if ( SOCKET_ERROR == result )
		result = 0;
	return result;
} 

int sg_write_bytes(const void *data, unsigned num)
{ 
	/* Write string to connection */
	int result;

	result = send(sSG384,(const char *)data,(int)num,0);
	if ( SOCKET_ERROR == result )
		result = 0;
	return result;
} 

void init_tcpip(void) 
{ 
	WSADATA wsadata; 
	if ( WSAStartup(2, &wsadata) != 0 ) { 
		printf("Unable to load windows socket library\n");
		exit(1); 
	} 
} 



int sg_read(char *buffer, unsigned num)
{ 
	/* Read up to num bytes from connection */
	int count;
	fd_set setRead, setWrite, setExcept;
	TIMEVAL tm;

	/* Use select() so we can timeout gracefully */
	tm.tv_sec = sg_timeout/1000;
	tm.tv_usec = (sg_timeout % 1000) * 1000;

	FD_ZERO(&setRead);
	FD_ZERO(&setWrite);
	FD_ZERO(&setExcept);
	FD_SET(sSG384,&setRead);
	count = select(0,&setRead,&setWrite,&setExcept,&tm);
	if ( count == SOCKET_ERROR ) {
		printf("select failed: connection aborted\n");
		//closesocket(sSG384);
		exit(1);
	} 
	count = 0;
	if ( FD_ISSET(sSG384,&setRead) ) {
		/* We've received something */
		count = (int)recv(sSG384,buffer,num-1,0);
		if ( SOCKET_ERROR == count ) {
			printf("Receive failed: connection aborted\n");
			//closesocket(sSG384);
			exit(1);
		} 
		else if (count ) {
			buffer[count] = '\0'; 
		} 
		else { 
			printf("Connection closed by remote host\n");
			//closesocket(sSG384);
			exit(1);
		} 
	} 
	return count;
}
