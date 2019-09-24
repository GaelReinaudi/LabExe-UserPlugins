#include "GRollingStats.h"

//! [Initialize the parameters]
GRollingStats::GRollingStats(QObject *parent, QString uniqueIdentifierName /* = "" */)
	: GProgDevice(parent, uniqueIdentifierName)
	, m_InputBucket("input", this)
    , m_Mean("Mean", this, GParam::ReadOnly)
	, m_StdDev("Std Dev", this, GParam::ReadOnly)
	, m_NormalStdDev("Std Dev / Mean", this, GParam::ReadOnly)
	, m_SampleSize("num. samples", this)
	, m_Reset("Reset", this)
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
	m_SampleSize = 10;
	// Connects the input bucket to the event that starts a calculation of the average
	connect(&m_InputBucket, SIGNAL(ValueUpdated(double)), this, SLOT(EventSampleArrived(double)));
	// Connects the \e reset parameter to the function that does Reset() the average.
	connect(&m_Reset, SIGNAL(ValueUpdated(bool)), this, SLOT(Reset()));
}
//! [Extra initialization the parameters]

GRollingStats::~GRollingStats()
{

}

/////////////////////////////////////////////////////////////////////
/*!
Populates a widget provided by a workbench in order to represent (and be adequately connected to) this GRollingStats. 
Layouts are used to make the widget react correctly to re-sizing.
The easiest way to connect the button and spinboxes to the actual instance of the corresponding parameter 
is to use the method GParamXXXX::ProvideNew----Widget(), that does all the necessary connections 
automatically (which would be the equivalent of this PopulateDeviceWidget(), but for a single parameter).
\param:  GDeviceWidget * theDeviceWidget : the parent widget in the gui.
*////////////////////////////////////////////////////////////////////
//[PopulateDeviceWidgetImplementation]
void GRollingStats::PopulateDeviceWidget(GDeviceWidget* theDeviceWidget )
{
	// We add a vertical layout to hold together all the widgets that we are going to display.
	QVBoxLayout* pVlay = new QVBoxLayout();
	theDeviceWidget->AddSubLayout(pVlay);
	// We insert a widget provided by the input param bucket.
	pVlay->addWidget(m_InputBucket.ProvideNewParamWidget(theDeviceWidget));
	// We add a form layout that will hold the numerical settings.
 	QFormLayout* pFLay = new QFormLayout();
	pVlay->addLayout(pFLay);
	// We add the parameter labels and spinboxes by using the convenient function from the GParam class
	pFLay->addRow(m_SampleSize.ProvideNewLabel(theDeviceWidget), m_SampleSize.ProvideNewParamSpinBox(theDeviceWidget));
	pFLay->addRow(m_Mean.ProvideNewLabel(theDeviceWidget), m_Mean.ProvideNewParamSpinBox(theDeviceWidget));
	pFLay->addRow(m_StdDev.ProvideNewLabel(theDeviceWidget), m_StdDev.ProvideNewParamSpinBox(theDeviceWidget));
	pFLay->addRow(m_NormalStdDev.ProvideNewLabel(theDeviceWidget), m_NormalStdDev.ProvideNewParamSpinBox(theDeviceWidget));
	// We add the reset button, once again by asking the GParamBool to provide its own button interface.
	pVlay->addWidget(m_Reset.ProvideNewParamButton(theDeviceWidget));
	// We add an expandable space.
	pVlay->addStretch();
}
//[PopulateDeviceWidgetImplementation]

double GRollingStats::UpdateMean()
{
	// best way would be to throw exception if the average doesn't make sense
	int NValuesToConsider = qMax(1, m_SampleSize.IntValue());

	int ValuesSummed = 0;
	double average = 0.0;
	// we average until we have enough samples
	foreach(double val, m_History) {
		average += val;
		ValuesSummed++;
		if(ValuesSummed == NValuesToConsider)
			break;
	}
	if(ValuesSummed == 0)
		return 0.0;
	m_Mean = average / double(ValuesSummed);
	UpdateStdDev(m_Mean);
	return m_Mean;
}

double GRollingStats::UpdateStdDev(double mean)
{
	// best way would be to throw exception if the average doesn't make sense
	int NValuesToConsider = qMax(1, m_SampleSize.IntValue());

	int ValuesSummed = 0;
	double StdDev = 0.0;
	// we average until we have enough samples
	foreach(double val, m_History) {
		StdDev += pow((val-mean),2);
		ValuesSummed++;
		if(ValuesSummed == NValuesToConsider)
			break;
	}
	if(ValuesSummed == 0)
		return 0.0;
	m_StdDev = pow(StdDev / double(ValuesSummed),(0.5));
	UpdateNormalStdDev(m_StdDev,mean);
	return m_StdDev;
}

double GRollingStats::UpdateNormalStdDev(double StdDev, double mean)
{
	m_NormalStdDev = StdDev / mean;
	return m_NormalStdDev;
}


void GRollingStats::Reset()
{
	m_History.clear();
	// Send the input right to the output since it is the only value we have
	m_Mean = m_InputBucket.DoubleValue();
	m_StdDev = 0.0;
	m_NormalStdDev = 0.0;
}

void GRollingStats::EventSampleArrived(double newValue)
{
	// prepends the new data to the beginning of the list
	m_History.prepend(newValue);

	// quick way to implement the history by removing the unused parameters
	int maxSize = qMax(1, m_SampleSize.IntValue());
	while(m_History.count() > maxSize) {
		m_History.removeLast();
	}

	// launches the average calculation and update the output
	UpdateMean();
}
