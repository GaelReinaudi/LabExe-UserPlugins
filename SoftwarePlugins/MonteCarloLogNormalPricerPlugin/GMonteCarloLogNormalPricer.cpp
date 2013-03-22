#include "GMonteCarloLogNormalPricer.h"
#include "BasicPayOff.h"
#include "GEquationPayOff.h"
#include "GMonteCarloLogNormalPricerWidget.h"

static int numPointsPlot = 200;
static double minRangePlot = 0.0;
static double maxRangePlot = 200.0;
static double numIntervalPlot = numPointsPlot - 1;
static double deltaSpot = (maxRangePlot - minRangePlot) / numIntervalPlot;

//! [Initialize the parameters]
GMonteCarloLogNormalPricer::GMonteCarloLogNormalPricer(QObject *parent, QString uniqueIdentifierName /* = "" */)
	: GProgDevice(parent, uniqueIdentifierName)
	, m_PathNumber("num paths", this)
	, m_VolBucket("Volatility", this)
	, m_ExpiryBucket("Expiry", this)
	, m_StrikeBucket("Strike", this)
	, m_InterestRate("Interest Rate", this)
	, m_Reset("Reset", this)
	, m_Run("Run", this)
	, m_CurrentPlotValues(numPointsPlot)
	, m_OutputBridgeToEmitManyValues("Output", this, GParam::ReadOnly)
	, m_pPayOff(0)
	, m_TotalNumberIteration(0)
	, m_PayOffType("PayOff", this)
	, m_EquationString("Equation", this)
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
	m_PathNumber = -10;
	m_VolBucket.SetParamValue(0.05);
	m_VolBucket.DefaultParam()->SetTypicalStep(0.01);
	m_InterestRate.SetParamValue(0.03);
	m_InterestRate.SetTypicalStep(0.01);
	m_ExpiryBucket.DefaultParam()->SetHardLimits(0.0, 99.99);
	m_ExpiryBucket.SetParamValue(3);
	m_ExpiryBucket.DefaultParam()->SetTypicalStep(0.1);
	m_PathNumber.SetTypicalStep(10);
	m_PayOffType = 0;

	m_StrikeBucket.SetParamValue(100.0);
	// Connects the \e reset parameter to the function that does Reset() the average.
	connect(&m_VolBucket, SIGNAL(ValueUpdated(double)), this, SLOT(Reset()));
	connect(&m_InterestRate, SIGNAL(ValueUpdated(double)), this, SLOT(Reset()));
	connect(&m_ExpiryBucket, SIGNAL(ValueUpdated(double)), this, SLOT(Reset()));
	connect(&m_PayOffType, SIGNAL(ValueUpdated(int)), this, SLOT(Reset()));
	connect(&m_StrikeBucket, SIGNAL(ValueUpdated(double)), this, SLOT(Reset()));
	connect(&m_EquationString, SIGNAL(ValueUpdated(QString)), this, SLOT(Reset()));
	connect(&m_Reset, SIGNAL(ValueUpdated(bool)), this, SLOT(Reset()));

	connect(&m_Run, SIGNAL(ValueUpdated(bool)), this, SLOT(StartStopThread(bool)));
	connect(this, SIGNAL(finished()), this, SLOT(StartStopThread()));

	Reset();
}
//! [Extra initialization the parameters]

GMonteCarloLogNormalPricer::~GMonteCarloLogNormalPricer()
{
	m_Run = false;
	if(!wait(5000))
		terminate();
}

/////////////////////////////////////////////////////////////////////
/*!
Populates a widget provided by a workbench in order to represent (and be adequately connected to) this GMonteCarloLogNormalPricer. 
Layouts are used to make the widget react correctly to re-sizing.
The easiest way to connect the button and spinboxes to the actual instance of the corresponding parameter 
is to use the method GParamXXXX::ProvideNew----Widget(), that does all the necessary connections 
automatically (which would be the equivalent of this PopulateDeviceWidget(), but for a single parameter).
\param:  GDeviceWidget * theDeviceWidget : the parent widget in the gui.
*////////////////////////////////////////////////////////////////////
void GMonteCarloLogNormalPricer::PopulateDeviceWidget(GDeviceWidget* theDeviceWidget )
{
	// We add a vertical layout to hold together all the widgets that we are going to display.
	QVBoxLayout* pVlay = new QVBoxLayout();
	theDeviceWidget->AddSubLayout(pVlay);
	pVlay->addWidget(new GMonteCarloLogNormalPricerWidget(this, theDeviceWidget));
	return;
}

void GMonteCarloLogNormalPricer::StartStopThread(bool doStart /*= false*/)
{
	if(doStart) {
		start();
	}
	else if(m_Run)
		m_Run = false;
}

double GMonteCarloLogNormalPricer::RandGaussianBySummation() const
{
	double result = 0;
	for (unsigned long i = 0; i < 12; i++)
		result += qrand() / static_cast<double>(RAND_MAX);
	result -= 6.0;
	return result;
}

void GMonteCarloLogNormalPricer::EventPlotValuesUpdated()
{
	// if the time since the last update is too small, let's not overload the plotting for nothing
	if(m_TimerLastUpdateEmitted.hasExpired(50)) {
		m_Mutex.lock();
		m_OutputBridgeToEmitManyValues.EmitManyValues(m_CurrentPlotValues);
		m_Mutex.unlock();
		m_TimerLastUpdateEmitted.start();
	}
}

void GMonteCarloLogNormalPricer::Reset()
{
	m_Mutex.lock();

	if(m_pPayOff)
		m_pPayOff->deleteLater();
	switch(m_PayOffType.IntValue()) {
		case 0:
			m_pPayOff = new GEuropeanCallPayOff(m_StrikeBucket.DoubleValue(), this);
			break;
		case 1:
			m_pPayOff = new GDigitalCallPayOff(m_StrikeBucket.DoubleValue(), this);
			break;
		case 2:
			m_pPayOff = new GEquationPayOff(m_EquationString, this);
			break;
	}

	m_CurrentPlotValues.clear();
	m_CurrentPlotValues.resize(numPointsPlot);
	m_CurrentPlotValues.fill(0.0);

	r = m_InterestRate;
	expiry = m_ExpiryBucket.DoubleValue();
	variance = m_VolBucket.DoubleValue();
	variance *= variance;
	variance *= expiry;

	m_Mutex.unlock();

	m_TimerLastUpdateEmitted.start();
	EventPlotValuesUpdated();
	m_TotalNumberIteration = 0;
}

void GMonteCarloLogNormalPricer::PlotRandIteration()
{
	m_Mutex.lock();
	GPayOff & thePayOff = *m_pPayOff;

	double rootVariance = sqrt(variance);
	double itoCorrection = -0.5 * variance;

	double currentSpot = minRangePlot;

	double previousSampleCount = m_TotalNumberIteration;
	m_TotalNumberIteration++;
	double OneOverNewSampleCount = 1/(double(m_TotalNumberIteration));

	// for each spot currentSpot, we will compute PayOff(exp(-r* - 0.5 * sigma^2))
	for(int i = 0; i < numPointsPlot; i++) {
		// for the average, we re multiply the averaged value by the number of sample
		// latter we will divide by the new number of samples
		m_CurrentPlotValues[i] *= previousSampleCount;

		double drawGauss = rootVariance * RandGaussianBySummation();
		double drawSpot = currentSpot * qExp(r * expiry + itoCorrection + drawGauss);
		double drawPayOff = thePayOff(drawSpot);
		m_CurrentPlotValues[i] += drawPayOff * qExp(-r * expiry);

		// for the average, we divide by the new number of samples
		m_CurrentPlotValues[i] *= OneOverNewSampleCount;
		currentSpot += deltaSpot;
	}
	m_Mutex.unlock();
	QMetaObject::invokeMethod(this, "EventPlotValuesUpdated");
}

void GMonteCarloLogNormalPricer::run()
{
	qsrand(m_TotalNumberIteration);

	int iteration = m_PathNumber.IntValue();

	// should we cycle this with a short pause
	bool ReIterateWithPause = iteration < 0;

	if(!ReIterateWithPause) {
		while(iteration-- && m_Run) {
			PlotRandIteration();
		}
	}
	else {
		while(m_Run && m_PathNumber.IntValue()) {
			int iterPlus = -iteration;
			while(iterPlus-- && m_Run) {
				PlotRandIteration();
				msleep(1000 / (qMax(1, abs(m_PathNumber.IntValue()))));
			}
		}
	}
}