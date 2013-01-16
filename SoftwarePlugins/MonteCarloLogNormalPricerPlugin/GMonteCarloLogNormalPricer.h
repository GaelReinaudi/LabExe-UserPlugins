#ifndef GMonteCarloLogNormalPricer_H
#define GMonteCarloLogNormalPricer_H

#include "device.h"
#include "param.h"

class GPayOff;
class GMonteCarloLogNormalPricerWidget;
/////////////////////////////////////////////////////////////////////
//! \brief The GMonteCarloLogNormalPricer class implements a GProgDevice.
/*!
This soft device allows you to define an input parameter by drag-and-dropping it in a param-bucket. 
When the input is updated, the average over the past \e n values is calculated and displayed at the output. 
The value of \e n is defined by a spin-box.
If there are not yet \e n values in the past history of the parameter, the average is made on all existing data. 
The reset button clears the history of the parameter.
*/
//[inheritance]
class GMonteCarloLogNormalPricer : public GProgDevice
//[inheritance]
{
	Q_OBJECT

public:

	//! Constructor
	GMonteCarloLogNormalPricer(QObject *parent, QString uniqueIdentifierName = "");
	~GMonteCarloLogNormalPricer();

public slots:
	//! Called when values are updated and available for plotting
	void EventPlotValuesUpdated();
	//! Resets the current data to start over
	void Reset();
	//! Calls the start function if true
	void StartStopThread(bool doStart = false);

protected:
	//! Re-implemented to provide a new widget adequately connected to this GMonteCarloLogNormalPricer.
	void PopulateDeviceWidget(GDeviceWidget* theDeviceWidget);
	//! Re-implemented to perform the simulation in a separate thread
	void run();

private:
	double RandGaussianBySummation() const;
	//! add a random point simulated to each point of the plot spot values
	void PlotRandIteration();


//! [variables]
private:
	//! the bucket for the input parameter
	GSingleParamBucket m_VolBucket;
	GSingleParamBucket m_ExpiryBucket;
	GSingleParamBucket m_StrikeBucket;
	GParamDouble m_InterestRate;
	//! the output of the filter
	//! the number of samples to average on.
	GParamInt m_PathNumber;
	//! a run boolean that will iterate the simulation for m_PathNumber extra points
	GParamBool m_Run;
	//! a reset boolean that will provide a reset button
	GParamBool m_Reset;
	//! Value that will cycle through the m_CurrentPlotValues in order to hack a plotting into update 
	GParamDouble m_OutputBridgeToEmitManyValues;

	//! an int for the default type of option
	GParamInt m_PayOffType;
	GParamString m_EquationString;
//! [variables]

private:
	//! the payoff used for calculating the value at expiry
	GPayOff* m_pPayOff;
	//! the current values for the plot
	GVectorDouble m_CurrentPlotValues;
	//! Mutex to protect the plot values 
	QMutex m_Mutex;
	//! Total Number Of Iteration
	int m_TotalNumberIteration;
	QElapsedTimer m_TimerLastUpdateEmitted;
	//! local variable for the separate thread
	double r;
	double expiry;
	double variance;

	friend class GMonteCarloLogNormalPricerWidget;
};

#endif // GMonteCarloLogNormalPricer_H
