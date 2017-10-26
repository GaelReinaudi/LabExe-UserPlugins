#ifndef GThorlabsTSP01_H
#define GThorlabsTSP01_H

#include "device.h"
#include "param.h"
#include "visa.h"
#include "TLTSP.h"

/////////////////////////////////////////////////////////////////////
//! \brief The GThorlabsTSP01 class implements a GProgDevice.
/*!
This soft device allows you to define an input parameter by drag-and-dropping it in a param-bucket. 
When the input is updated, the average over the past \e n values is calculated and displayed at the output. 
The value of \e n is defined by a spin-box.
If there are not yet \e n values in the past history of the parameter, the average is made on all existing data. 
The reset button clears the history of the parameter.
*/
//[inheritance]
class GThorlabsTSP01 : public GProgDevice
//[inheritance]
{
	Q_OBJECT

public:

//[constructor]
	//! Constructor
	GThorlabsTSP01(QObject *parent, QString uniqueIdentifierName = "");
//[constructor]
	~GThorlabsTSP01();

public slots:
	//! Makes the filter to compute the output based on the History of the parameter being filtered
	void StartUpdateOutput();
	void UpdateOutput();
	//! Resets the filter by setting the output equal to the input and emptying the history
	//void Reset();

//![PopulateDeviceWidget]
protected:
	//! Re-implemented to provide a new widget adequately connected to this GThorlabsTSP01.
	void PopulateDeviceWidget(GDeviceWidget* theDeviceWidget);
//![PopulateDeviceWidget]

//! [variables]
private:
//! [variablesInputBucket]
	//! the bucket for the input parameter
	GSingleParamBucket m_InputBucket;
	GParamDouble m_OutputT1;//internal
	GParamDouble m_OutputT2;//external TH1
	GParamDouble m_OutputT3;//external TH2
	GParamDouble m_OutputH;
	GParamBool m_EnableTrigger;
	GParamBool m_ManualTrigger;
//! [variablesInputBucket]

private slots:
	//! Called when a sample arrives and computes the new output.
	void ManualTriggered();
	void error_exit(ViSession instrHdl, ViStatus err);
	ViStatus find_instruments(ViString findPattern, ViChar **resource);
};

#endif // GThorlabsTSP01_H
