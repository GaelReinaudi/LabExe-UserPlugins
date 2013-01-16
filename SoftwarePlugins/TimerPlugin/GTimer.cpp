#include "GTimer.h"

//! [Initialize the parameters]
GTimer::GTimer(QObject *parent, QString uniqueIdentifierName /* = "" */)
	: GProgDevice(parent, uniqueIdentifierName)
	, m_Delay("Triger delay time (hh:mm;ss.zzz)", this)
	, m_SingleShot("Single shot (vs continuous)?", this)
	, m_NumTriggers("Number of triggers", this)
	, m_ElapsedTime("Elapsed time (s)", this)
	, m_OutputBucket("Timer output bucket", this, GParam::ReadOnly)
	, m_Status("Status", this)
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
	//m_Delay = 1000;//Default is 1 second. 
	//m_Delay.SetHardLimits(100, 1e6);//hard limits. 
	m_Delay = "00:00;01.000";//1 second
	m_SingleShot = false;//Default is cotinuous trigger. 
	m_NumTriggers = -1;
	m_ElapsedTime = -1;
	m_OutputBucket.Freeze(true);// Do not want drag/drop of new variables in this bucket. 
	m_Status = false;

	// Connections:  
	// -- After saved GParam values are loaded, make sure propagate changes from default values: 
	//connect(this, SIGNAL(ParamJustInterpretSettings()), this, SLOT(InitSavedSettings()));
}
//! [Extra initialization the parameters]

GTimer::~GTimer()
{	
}

/////////////////////////////////////////////////////////////////////
/*!
Populates a widget provided by a workbench in order to represent (and be adequately connected to) this GTimer. 
Layouts are used to make the widget react correctly to re-sizing.
The easiest way to connect the button and spinboxes to the actual instance of the corresponding parameter 
is to use the method GParamXXXX::ProvideNew----Widget(), that does all the necessary connections 
automatically (which would be the equivalent of this PopulateDeviceWidget(), but for a single parameter).
\param:  GDeviceWidget * theDeviceWidget : the parent widget in the gui.
*////////////////////////////////////////////////////////////////////
//[PopulateDeviceWidgetImplementation]
void GTimer::PopulateDeviceWidget(GDeviceWidget* theDeviceWidget )
{	//Overall layout is vertical box
	QVBoxLayout* pVlay = new QVBoxLayout();
	theDeviceWidget->AddSubLayout(pVlay);
	
	//Parameters: 
	QGroupBox* inputBox = new QGroupBox(tr("Timer settings:"));
	QFormLayout* pFlay = new QFormLayout();
	inputBox->setLayout(pFlay);
	pVlay->addWidget(inputBox);
	pFlay->addRow(m_Delay.ProvideNewLabel(theDeviceWidget), m_Delay.ProvideNewParamLineEdit(theDeviceWidget));
	QCheckBox* singleShotCheckBox = m_SingleShot.ProvideNewParamCheckBox(theDeviceWidget);
	singleShotCheckBox->setText("");
	pFlay->addRow(m_SingleShot.ProvideNewLabel(theDeviceWidget), singleShotCheckBox); //m_SingleShot.ProvideNewParamCheckBox(theDeviceWidget));

	//Output bucket: 
	GParamBucketWidget* pOutWid = m_OutputBucket.ProvideParamBucketWidget(theDeviceWidget);
	pOutWid->setTitle("Timer outputs:");
	pOutWid->UseHighLightDecay(true);
	m_OutputBucket.AddParam(&m_NumTriggers);//Link bucket to respective GParam's. 
	m_OutputBucket.AddParam(&m_ElapsedTime);
	pVlay->addWidget(pOutWid);

	//Add Start/Stop button: 
	statusButton = new QPushButton(tr("Start Timer"));
	statusButton->setCheckable(false);
	statusButton->setStyleSheet("background: green");
	pVlay->addWidget(statusButton);
	connect(statusButton, SIGNAL(clicked()), this, SLOT(UserChangeStatus()));
	
	//Syntax examples: 
	//pVlay->addWidget(m_InputBucket.ProvideParamBucketWidget(theDeviceWidget)); 
	//pFLay->addRow(m_DoTimeLapse.ProvideNewParamCheckBox(theDeviceWidget), m_TimeLapse.ProvideNewParamSpinBox(theDeviceWidget));
	//pFLay->addRow(m_TimeLapse.ProvideNewLabel(theDeviceWidget), m_TimeLapse.ProvideNewParamSpinBox(theDeviceWidget));
	//pFLay->addRow(m_Output.ProvideNewLabel(theDeviceWidget), m_Output.ProvideNewParamSpinBox(theDeviceWidget));
	
	//End the vertical layout with an extendable space
	pVlay->addStretch(); 

	//Initialize timer
	m_Timer = new QTimer(this);

	// Connections:  
	// -- Timer triggers TimerTriggered()
	connect(m_Timer, SIGNAL(timeout()), this, SLOT(TimerTriggered()));
}
//[PopulateDeviceWidgetImplementation]


void GTimer::UserChangeStatus()
{	//This is called when the statusButton is clicked by the user. 

	if(m_Status)//m_Timer->isActive())//m_Status)
	{	//User wants to stop the timer: 
		m_Timer->stop();
		
		m_Status = false;
		m_NumTriggers = -1;
		m_ElapsedTime = -1;

		//Update button status
		statusButton->setStyleSheet("background: green");
		statusButton->setText(tr("Start Timer"));
	}
	else 
	{	//User wants to start the timer:
		
		//Get delay time from user: 
		QTime q_Delay = QTime::fromString(m_Delay.StringValue(),"hh:mm;ss.zzz");
		
		//Error checking: 
		if(q_Delay.isValid())
		{	int msecDelay = QTime::QTime(0,0,0,0).msecsTo(q_Delay);//ms
			if((msecDelay >= 100)&&(msecDelay < 24*60*60*1000))//Hard limits, 0.1s to 1day.
			{	
				//Start timer: 
				m_Timer->setSingleShot(m_SingleShot);//Set single-shot status
				m_Timer->start(msecDelay);
				m_Status = true; 
				m_NumTriggers = 0;
				m_ElapsedTime = 0;
				q_StartTime = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0;

				//Update button status
				statusButton->setStyleSheet("background: red");
				statusButton->setText(tr("Stop Timer"));
			}
		}

	}
}

void GTimer::TimerTriggered()
{	//Update outputs: 
	m_NumTriggers = m_NumTriggers.IntValue() + 1;
	m_ElapsedTime = QDateTime::currentDateTime().toMSecsSinceEpoch()/1000.0 - q_StartTime;

	if(!m_Timer->isActive())
	{	//If timer exits single shot, then reset: 
		m_Status = false;
		//Don't update these, so user can tell what happened? 
		//m_NumTriggers = -1;
		//m_ElapsedTime = -1;

		//Update button status
		statusButton->setStyleSheet("background: green");
		statusButton->setText(tr("Start Timer"));
	}
}