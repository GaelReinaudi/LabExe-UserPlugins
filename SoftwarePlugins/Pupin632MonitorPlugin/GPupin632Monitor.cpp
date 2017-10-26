#include "GPupin632Monitor.h"
#include <QWebEngineView>
#include <QWebEnginePage>
#include <QWebEngineFrame>
// #include <QTimer>
// #include <QFile>
// #include <QTextStream>
// #include <QDateTime>
// #include <QDebug>

//! [Initialize the parameters]
GPupin632Monitor::GPupin632Monitor(QObject *parent, QString uniqueIdentifierName /* = "" */)
	: GProgDevice(parent, uniqueIdentifierName)
	, m_InputBucket("Trigger", this)
	, m_EnableTrigger("Enable Triggering?", this)
	, m_ManualTrigger("Manually Get New Values", this)
	, m_OurLabUrl("http://128.59.169.94/pe/webAhu6001")
	, m_tempSE("SE Space Temp (F)", this, GParam::ReadOnly)
	, m_tempN("N Space Temp (F)", this, GParam::ReadOnly)
	, m_tempW("W Space Temp (F)", this, GParam::ReadOnly)
	, m_humSet("Space Humidity Setpoint", this, GParam::ReadOnly)
	, m_humDisch("Discharge Air Humidity", this, GParam::ReadOnly)
	, m_humSpace("Space Humidity %", this, GParam::ReadOnly)
	, m_Airflow("Airflow (CFM)", this, GParam::ReadOnly)
	, m_FanSpeed("Supply Fan Speed %", this, GParam::ReadOnly)
	, m_tempDisch("Discharge Air Temp (F)", this, GParam::ReadOnly)
	, m_tempAvg("Avg Space Temp (F)", this, GParam::ReadOnly)
	, m_tempSet("Space Temp Setpoint", this, GParam::ReadOnly)
	, m_humidifier("Humidifier %", this, GParam::ReadOnly)
	, m_antitemp("Anti Room Temp (F)", this, GParam::ReadOnly)
	, m_antitempSet("Anti Room Setpoint", this, GParam::ReadOnly)
	, m_OAtemp("Outside Air Temp (F)", this, GParam::ReadOnly)
	, m_OAhum("Outside Air Humidity (%)", this, GParam::ReadOnly)
	, m_RetTemp("Return Air Temp (F)", this, GParam::ReadOnly)
	, m_RetHum("Return Air Humidity (%)", this, GParam::ReadOnly)
	, m_UpdateStatus("Update status:", this)
	, m_AmIUpdating("", this)
	, TheWebView()
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
	m_tempSE = -1;
	m_tempN = -1;
	m_tempW = -1;
	m_humSpace = -1;
	m_humDisch = -1; 
	m_humSet = -1; 
	m_Airflow = -1;
	m_FanSpeed = -1;
	m_tempDisch = -1;
	m_tempAvg = -1;
	m_tempSet = -1;
	m_humidifier = -1;
	m_antitemp = -1;
	m_antitempSet = -1;
	m_OAtemp = -1;
	m_OAhum = -1;
	m_RetTemp = -1;
	m_RetHum = -1;

	m_tempSE.SetDisplayDecimals(1);
	m_tempN.SetDisplayDecimals(1);
	m_tempW.SetDisplayDecimals(1);
	m_humSpace.SetDisplayDecimals(0);
	m_humDisch.SetDisplayDecimals(0);
	m_humSet.SetDisplayDecimals(0);
	m_Airflow.SetDisplayDecimals(0);
	m_FanSpeed.SetDisplayDecimals(0);
	m_tempDisch.SetDisplayDecimals(1);
	m_tempAvg.SetDisplayDecimals(1);
	m_tempSet.SetDisplayDecimals(1);
	m_humidifier.SetDisplayDecimals(0);
	m_antitemp.SetDisplayDecimals(1);
	m_antitempSet.SetDisplayDecimals(1);
	m_OAtemp.SetDisplayDecimals(1);
	m_OAhum.SetDisplayDecimals(0);
	m_RetTemp.SetDisplayDecimals(1);
	m_RetHum.SetDisplayDecimals(0);

	m_EnableTrigger = false;
	m_ManualTrigger = false;
	m_UpdateStatus = "(Unused)";
	m_AmIUpdating = false;

	// Connects the input bucket to trigger reading the sensor values: 
	connect(&m_InputBucket, SIGNAL(ValueUpdated(double)), this, SLOT(StartUpdateOutput()));
	// Manual trigger: 
	connect(&m_ManualTrigger, SIGNAL(ValueUpdated(bool)), this, SLOT(ManualTriggered()));
	// After each webpage is sucessfully loaded, get values: 
	TheWebView = new QWebEngineView();
	connect(TheWebView, SIGNAL(loadFinished(bool)), this, SLOT(UpdateOutput(bool)));
}
//! [Extra initialization the parameters]

GPupin632Monitor::~GPupin632Monitor()
{

}

/////////////////////////////////////////////////////////////////////
/*!
Populates a widget provided by a workbench in order to represent (and be adequately connected to) this GPupin632Monitor.
Layouts are used to make the widget react correctly to re-sizing.
The easiest way to connect the button and spinboxes to the actual instance of the corresponding parameter 
is to use the method GParamXXXX::ProvideNew----Widget(), that does all the necessary connections 
automatically (which would be the equivalent of this PopulateDeviceWidget(), but for a single parameter).
\param:  GDeviceWidget * theDeviceWidget : the parent widget in the gui.
*////////////////////////////////////////////////////////////////////
//[PopulateDeviceWidgetImplementation]


void GPupin632Monitor::PopulateDeviceWidget(GDeviceWidget* theDeviceWidget )
{
	// We add a vertical layout to hold together all the widgets that we are going to display.
	QVBoxLayout* pVlay = new QVBoxLayout();
	theDeviceWidget->AddSubLayout(pVlay);
	// We insert a widget provided by the input param bucket.
	pVlay->addWidget(m_InputBucket.ProvideNewParamWidget(theDeviceWidget));
	//pVlay->addWidget(m_OutputT1.ProvideNewParamWidget(theDeviceWidget));
	//pVlay->addWidget(m_OutputT2.ProvideNewParamWidget(theDeviceWidget));
	//pVlay->addWidget(m_OutputH.ProvideNewParamWidget(theDeviceWidget));
	// We add a form layout that will hold the outputs.
  	QFormLayout* pFLay = new QFormLayout();
 	pVlay->addLayout(pFLay);
	//Update status text box: 
	pFLay->addRow(m_UpdateStatus.ProvideNewLabel(theDeviceWidget), m_UpdateStatus.ProvideNewParamLineEdit(theDeviceWidget));
 	// We add the parameter labels and spinboxes by using the convenient function from the GParam class
	// Arrange in order following the website: 
	pFLay->addRow(m_RetTemp.ProvideNewLabel(theDeviceWidget), m_RetTemp.ProvideNewParamSpinBox(theDeviceWidget));
	pFLay->addRow(m_RetHum.ProvideNewLabel(theDeviceWidget), m_RetHum.ProvideNewParamSpinBox(theDeviceWidget));
	pFLay->addRow(m_Airflow.ProvideNewLabel(theDeviceWidget), m_Airflow.ProvideNewParamSpinBox(theDeviceWidget));
	pFLay->addRow(m_FanSpeed.ProvideNewLabel(theDeviceWidget), m_FanSpeed.ProvideNewParamSpinBox(theDeviceWidget));
	pFLay->addRow(m_tempDisch.ProvideNewLabel(theDeviceWidget), m_tempDisch.ProvideNewParamSpinBox(theDeviceWidget));
	pFLay->addRow(m_humDisch.ProvideNewLabel(theDeviceWidget), m_humDisch.ProvideNewParamSpinBox(theDeviceWidget));
 	pFLay->addRow(m_tempSE.ProvideNewLabel(theDeviceWidget), m_tempSE.ProvideNewParamSpinBox(theDeviceWidget));
	pFLay->addRow(m_tempN.ProvideNewLabel(theDeviceWidget), m_tempN.ProvideNewParamSpinBox(theDeviceWidget));
	pFLay->addRow(m_tempW.ProvideNewLabel(theDeviceWidget), m_tempW.ProvideNewParamSpinBox(theDeviceWidget));
	pFLay->addRow(m_tempAvg.ProvideNewLabel(theDeviceWidget), m_tempAvg.ProvideNewParamSpinBox(theDeviceWidget));
	pFLay->addRow(m_tempSet.ProvideNewLabel(theDeviceWidget), m_tempSet.ProvideNewParamSpinBox(theDeviceWidget));
	pFLay->addRow(m_humSpace.ProvideNewLabel(theDeviceWidget), m_humSpace.ProvideNewParamSpinBox(theDeviceWidget));
	pFLay->addRow(m_humSet.ProvideNewLabel(theDeviceWidget), m_humSet.ProvideNewParamSpinBox(theDeviceWidget));
	pFLay->addRow(m_humidifier.ProvideNewLabel(theDeviceWidget), m_humidifier.ProvideNewParamSpinBox(theDeviceWidget));
	pFLay->addRow(m_antitemp.ProvideNewLabel(theDeviceWidget), m_antitemp.ProvideNewParamSpinBox(theDeviceWidget));
	pFLay->addRow(m_antitempSet.ProvideNewLabel(theDeviceWidget), m_antitempSet.ProvideNewParamSpinBox(theDeviceWidget));
	pFLay->addRow(m_OAhum.ProvideNewLabel(theDeviceWidget), m_OAhum.ProvideNewParamSpinBox(theDeviceWidget));	
	pFLay->addRow(m_OAtemp.ProvideNewLabel(theDeviceWidget), m_OAtemp.ProvideNewParamSpinBox(theDeviceWidget));
	

// 	// We add the reset button, once again by asking the GParamBool to provide its own button interface.
 	pVlay->addWidget(m_ManualTrigger.ProvideNewParamButton(theDeviceWidget));
	//QDialogButtonBox* boxButtons = new QDialogButtonBox(Qt::Vertical);
	//QPushButton* manualTriggerButton = new QPushButton(tr("Get New Values"));
	//connect(manualTriggerButton, SIGNAL(clicked()), this, SLOT(ManualTriggered()));
	//boxButtons->addButton(manualTriggerButton, QDialogButtonBox::ActionRole);
	//pVlay->addWidget(boxButtons);
 	pVlay->addWidget(m_EnableTrigger.ProvideNewParamCheckBox(theDeviceWidget));
 	// We add an expandable space.
 	pVlay->addStretch();
}
//[PopulateDeviceWidgetImplementation]


void GPupin632Monitor::StartUpdateOutput()
{	
	//This function is called when the trigger input bucket is updated. 
	// Check if triggering enabled: 
	if(m_EnableTrigger)//Prevent fast repeated triggering...
	{	//Yes, let's update the outputs. 
		m_UpdateStatus = "Triggered...";
		GetWebpage();
	}
	
}

void GPupin632Monitor::GetWebpage()
{	if(m_AmIUpdating)//Prevent fast triggering from creating multiple webpage load requests. 
	{	m_UpdateStatus = "Trigger ignored! Not done with previous trigger.";
		return;
	}
	
	//OK, let's try to load the facilities webpage: 
	Thehtml = "";
	TheWebView->load(QUrl(m_OurLabUrl));
	Thehtml = TheWebView->page()->mainFrame()->toHtml();
	
	m_AmIUpdating = true; 
	m_UpdateStatus = "Loading webpage...";
	//qDebug()<<"Pupin632: trying to load webpage...";
	//if loading finishes, a connection made above then triggers UpdateOutput(). 	
}

void GPupin632Monitor::UpdateOutput(bool ok)
{	//OK, let's extract values from the facilities webpage: 
	
	if(!ok)
	{	m_UpdateStatus = "Failed to load webpage!";
		m_AmIUpdating = false; 
		qDebug()<<"Pupin632: webpage failed to load successfully...";

		m_tempSE = -1;
		m_tempN = -1;
		m_tempW = -1;
		m_humSpace = -1;
		m_humDisch = -1; 
		m_humSet = -1;
		m_Airflow = -1;
		m_FanSpeed = -1;
		m_tempDisch = -1;
		m_tempAvg = -1;
		m_tempSet = -1;
		m_humidifier = -1;
		m_antitemp = -1;
		m_antitempSet = -1;
		m_OAtemp = -1;
		m_OAhum = -1;
		m_RetTemp = -1;
		m_RetHum = -1;
		return;
	}
	m_UpdateStatus = "Webpage loaded OK.";
	m_AmIUpdating = false;
	//qDebug()<<"Pupin632: webpage loaded successfully!";
	//qDebug()<<"Pupin632: webpage title: "<<TheWebView->title();
	

	m_tempN.SetParamValue(ExtractValueFromWebpage("<td>N. Space Temp",6));
	m_tempSE.SetParamValue(ExtractValueFromWebpage("<td>S.E. Space Temp",6));
	m_tempW.SetParamValue(ExtractValueFromWebpage("<td>W. Space Temp",6));
	m_humSpace.SetParamValue(ExtractValueFromWebpage("<td>Space Humidity",3));
	m_humDisch.SetParamValue(ExtractValueFromWebpage("<td>Discharge Air Humidity",3));
	m_humSet.SetParamValue(ExtractValueFromWebpage("<td>Space Humidity Setpoint",3));
	m_Airflow.SetParamValue(ExtractValueFromWebpage("<td>Airflow",5));
	m_FanSpeed.SetParamValue(ExtractValueFromWebpage("<td>Supply Fan Speed",4));
	m_tempDisch.SetParamValue(ExtractValueFromWebpage("<td>Discharge Air Temp",6));
	m_tempAvg.SetParamValue(ExtractValueFromWebpage("<td>Avg. Space Temp",6));
	m_tempSet.SetParamValue(ExtractValueFromWebpage("<td>Space Temp Setpoint",6));
	m_humidifier.SetParamValue(ExtractValueFromWebpage("<td>Humidifier",4));
	m_antitemp.SetParamValue(ExtractValueFromWebpage("<td>Anti Room Temp",6));
	m_antitempSet.SetParamValue(ExtractValueFromWebpage("<td>Anti Room  Setpoint",6));
	m_OAtemp.SetParamValue(ExtractValueFromWebpage("<td>OA Temp",6));
	m_OAhum.SetParamValue(ExtractValueFromWebpage("<td>OA Humidity",3));
	m_RetTemp.SetParamValue(ExtractValueFromWebpage("<td>Return Air Temp",6));
	m_RetHum.SetParamValue(ExtractValueFromWebpage("<td>Return Air Humidity",3));
	
}

double GPupin632Monitor::ExtractValueFromWebpage(QString FieldName, int cut)
{	int indexN = Thehtml.indexOf(FieldName);
	if(indexN == -1)
	{	//Not found!
		return -1;
	}
 	int indexNnum = Thehtml.indexOf("</td><td>", indexN) + 9;//Puts us right after "</td><td>".
	if(indexN == -1)
	{	//Not found!
		return -1;
	}
 	QString stnum = Thehtml.mid(indexNnum, cut);
	//qDebug()<<stnum;
 	return stnum.toDouble();
}

void GPupin632Monitor::ManualTriggered()
{	m_UpdateStatus = "Manually triggered...";
	GetWebpage();
}
