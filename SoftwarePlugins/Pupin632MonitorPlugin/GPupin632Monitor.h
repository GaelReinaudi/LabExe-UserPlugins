#ifndef GPupin632Monitor_H
#define GPupin632Monitor_H

#include "device.h"
#include <QWebEngineView>
#include <QWebEnginePage>
#include <QWebEngineFrame>
#include "param.h"

/////////////////////////////////////////////////////////////////////
//! \brief The GPupin632Monitor class implements a GProgDevice.
/*!
This soft device allows you to define an input parameter by drag-and-dropping it in a param-bucket. 
When the input is updated, the average over the past \e n values is calculated and displayed at the output. 
The value of \e n is defined by a spin-box.
If there are not yet \e n values in the past history of the parameter, the average is made on all existing data. 
The reset button clears the history of the parameter.
*/
class GPupin632Monitor : public GProgDevice
{
	Q_OBJECT

public:
	GPupin632Monitor(QObject *parent, QString uniqueIdentifierName = "");

public slots:
	//! 
	//void Reset();

//![PopulateDeviceWidget]
protected:
	//! Re-implemented to provide a new widget adequately connected to this GPupin632Monitor.
	void PopulateDeviceWidget(GDeviceWidget* theDeviceWidget);
//![PopulateDeviceWidget]

//! [variables]
private:
//! [variablesInputBucket]
	//! the bucket for the input parameter
	GSingleParamBucket m_InputBucket;
	GParamBool m_EnableTrigger;
	GParamBool m_ManualTrigger;
	
	QWebEngineView* TheWebView;
	QString Thehtml;
	QString m_OurLabUrl;
	
	GParamString m_UpdateStatus;//text to tell the user what's going on. 
	GParamBool m_AmIUpdating;//bool to prevent rapid retriggering while slow webpage loading is happening. 

	GParamDouble m_tempSE;
	GParamDouble m_tempN;
	GParamDouble m_tempW;
	GParamDouble m_humSet;
	GParamDouble m_humDisch;
	GParamDouble m_humSpace;

	GParamDouble m_Airflow;
	GParamDouble m_FanSpeed;
	GParamDouble m_tempDisch;
	GParamDouble m_tempAvg;
	GParamDouble m_tempSet;
	GParamDouble m_humidifier;
	GParamDouble m_antitemp;
	GParamDouble m_antitempSet;
	GParamDouble m_OAtemp;
	GParamDouble m_OAhum;
	GParamDouble m_RetTemp;
	GParamDouble m_RetHum;

//! [variablesInputBucket]

private slots:
	//! 
	void StartUpdateOutput();
	void UpdateOutput(bool ok);
	void ManualTriggered();
	void GetWebpage();
	double ExtractValueFromWebpage(QString FieldName, int cut);
};

#endif // GPupin632Monitor_H
