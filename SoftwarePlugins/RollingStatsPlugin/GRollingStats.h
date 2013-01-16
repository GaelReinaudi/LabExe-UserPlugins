#ifndef GRollingStats_H
#define GRollingStats_H

#include "device.h"
#include "param.h"
/////////////////////////////////////////////////////////////////////
//! \brief The GRollingStats class implements a GProgDevice.
/*!
This soft device allows you to define an input parameter by drag-and-dropping it in a param-bucket. 
When the input is updated, the average over the past \e n values is calculated and displayed at the output. 
The value of \e n is defined by a spin-box.
If there are not yet \e n values in the past history of the parameter, the average is made on all existing data. 
The reset button clears the history of the parameter.
*/
//[inheritance]
class GRollingStats : public GProgDevice
//[inheritance]
{
	Q_OBJECT

public:

//[constructor]
	//! Constructor
	GRollingStats(QObject *parent, QString uniqueIdentifierName = "");
//[constructor]
	~GRollingStats();

public slots:
	//! Makes the filter to compute the output based on the History of the parameter being filtered
	double UpdateMean();
	double UpdateStdDev(double mean);
	double UpdateNormalStdDev(double StdDev, double mean);
	//! Resets the filter by setting the output equal to the input and emptying the history
	void Reset();

//![PopulateDeviceWidget]
protected:
	//! Re-implemented to provide a new widget adequately connected to this GRollingStats.
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
	GParamDouble m_Mean;
	GParamDouble m_StdDev;
	GParamDouble m_NormalStdDev;
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

private slots:
	//! Called when a sample arrives and computes the new output.
	void EventSampleArrived(double newValue);
};

#endif // GRollingStats_H
