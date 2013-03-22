#ifndef GLowPassFilter_H
#define GLowPassFilter_H

#include "device.h"
#include "param.h"
/////////////////////////////////////////////////////////////////////
//! \brief The GLowPassFilter class implements a GProgDevice.
/*!
This soft device allows you to define an input parameter by drag-and-dropping it in a param-bucket. 
When the input is updated, the average over the past \e n values is calculated and displayed at the output. 
The value of \e n is defined by a spin-box.
If there are not yet \e n values in the past history of the parameter, the average is made on all existing data. 
The reset button clears the history of the parameter.
*/
//[inheritance]
class GLowPassFilter : public GProgDevice
//[inheritance]
{
	Q_OBJECT

public:

//[constructor]
	//! Constructor
	GLowPassFilter(QObject *parent, QString uniqueIdentifierName = "");
//[constructor]
	~GLowPassFilter();

public slots:
	//! Makes the filter to compute the output based on the History of the parameter being filtered
	void UpdateOutput();
	//! Resets the filter by setting the output equal to the input and emptying the history
	void Reset();

//![PopulateDeviceWidget]
protected:
	//! Re-implemented to provide a new widget adequately connected to this GLowPassFilter.
	void PopulateDeviceWidget(GDeviceWidget* theDeviceWidget);
//![PopulateDeviceWidget]

//! [variables]
private:
//! [variablesInputBucket]
	//! the bucket for the input parameter
	GSingleParamBucket m_InputBucket;
//! [variablesInputBucket]
//! [variablesOutput]
	//! the output of the filter
	GParamDouble m_Output;
//! [variablesOutput]
//! [variablesSampleSize]
	//! the number of samples to average on.
	GParamInt m_SampleSize;
//! [variablesSampleSize]
//! [variablesReset]
	//! a reset boolean that will provide a reset button
	GParamBool m_Reset;
//! [variablesReset]
	//! the history of the values of the parameters
	QList<double> m_History;
//! [variables]
	//! A bool to tell if we should use a time lapse rather than a given number of samples
	GParamBool m_DoTimeLapse;
	//! Timer lapse on which to average until releasing a value
	GParamDouble m_TimeLapse;
	QTimer m_LapseTimer;

private slots:
	//! Called when a sample arrives and computes the new output.
	void EventSampleArrived(double newValue);
};

#endif // GLowPassFilter_H
