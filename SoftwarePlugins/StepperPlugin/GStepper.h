#ifndef GStepper_H
#define GStepper_H

#include "device.h"
#include "param.h"

/////////////////////////////////////////////////////////////////////
//! \brief The GStepper class implements a GProgDevice.
/*!
This soft device allows you to define an input parameter by drag-and-dropping it in a param-bucket. 
When the input is updated, the average over the past \e n values is calculated and displayed at the output. 
The value of \e n is defined by a spin-box.
If there are not yet \e n values in the past history of the parameter, the average is made on all existing data. 
The reset button clears the history of the parameter.
*/
//[inheritance]
class GStepper : public GProgDevice
//[inheritance]
{
	Q_OBJECT

public:

//[constructor]
	//! Constructor
	GStepper(QObject *parent, QString uniqueIdentifierName = "");
//[constructor]
	~GStepper();

public slots:
	//! Makes the filter to compute the output based on the History of the parameter being filtered
	void StartUpdateOutput();
	void UpdateOutput();
	//! Resets the filter by setting the output equal to the input and emptying the history
	void Reset();

//![PopulateDeviceWidget]
protected:
	//! Re-implemented to provide a new widget adequately connected to this GStepper.
	void PopulateDeviceWidget(GDeviceWidget* theDeviceWidget);
//![PopulateDeviceWidget]

//! [variables]
private:
//! [variablesInputBucket]
	//! the bucket for the input parameter
	GSingleParamBucket m_InputBucket;
	GSingleParamBucket m_OutputBucket;
//! [variablesInputBucket]
//! [variablesReset]
	//! a reset boolean that will provide a reset button
	GParamBool m_Reset;
	GParamBool m_Enable;
//! [variablesReset]
//! [variablesOutput]
	//! the output of the filter
	//GParamDouble m_Output;
	GParamDouble m_Start;
	GParamDouble m_StepSize;
	GParamDouble m_Maximum;
	GParamDouble m_Delay;
	double m_CurrentFreq;
//! [variablesOutput]
//! [variablesSampleSize]
	//! the number of samples to average on.
	//GParamInt m_SampleSize;
	GParamInt m_Steps;
	GParamInt m_CurrentStep;
	GParamInt m_PointsPerStep;
//! [variablesSampleSize]
	//! the history of the values of the parameters
	QList<double> m_History;
//! [variables]

private slots:
	//! Called when a sample arrives and computes the new output.
	//void EventSampleArrived(double newValue);
	void SetSteps();
	//void SetStepSize(double steps);
};

#endif // GStepper_H
