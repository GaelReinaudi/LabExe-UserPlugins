#include "GLowPassFilter.h"

//! [Initialize the parameters]
GLowPassFilter::GLowPassFilter(QObject *parent, QString uniqueIdentifierName /* = "" */)
	: GProgDevice(parent, uniqueIdentifierName)
	, m_SampleSize("num. samples", this)
	, m_InputBucket("input", this)
	, m_Output("out", this, GParam::ReadOnly)
	, m_Reset("Reset", this)
	, m_DoTimeLapse("Do time lapse", this)
	, m_TimeLapse("Lapse [s]", this)
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
	m_SampleSize.SetHardLimits(0, 1e9);
	// Connects the input bucket to the event that starts a calculation of the average
	connect(&m_InputBucket, SIGNAL(ValueUpdated(double)), this, SLOT(EventSampleArrived(double)));
	// Connects the \e reset parameter to the function that does Reset() the average.
	connect(&m_Reset, SIGNAL(ValueUpdated(bool)), this, SLOT(Reset()));
	// if time lapse changes, reset
	connect(&m_DoTimeLapse, SIGNAL(ValueUpdated(bool)), this, SLOT(Reset()));
	connect(&m_TimeLapse, SIGNAL(ValueUpdated(double)), this, SLOT(Reset()));
	connect(&m_LapseTimer, SIGNAL(timeout()), this, SLOT(UpdateOutput()));
}
//! [Extra initialization the parameters]

GLowPassFilter::~GLowPassFilter()
{

}

/////////////////////////////////////////////////////////////////////
/*!
Populates a widget provided by a workbench in order to represent (and be adequately connected to) this GLowPassFilter. 
Layouts are used to make the widget react correctly to re-sizing.
The easiest way to connect the button and spinboxes to the actual instance of the corresponding parameter 
is to use the method GParamXXXX::ProvideNew----Widget(), that does all the necessary connections 
automatically (which would be the equivalent of this PopulateDeviceWidget(), but for a single parameter).
\param:  GDeviceWidget * theDeviceWidget : the parent widget in the gui.
*////////////////////////////////////////////////////////////////////
//[PopulateDeviceWidgetImplementation]
void GLowPassFilter::PopulateDeviceWidget(GDeviceWidget* theDeviceWidget )
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

	pFLay->addRow(m_DoTimeLapse.ProvideNewParamCheckBox(theDeviceWidget), m_TimeLapse.ProvideNewParamSpinBox(theDeviceWidget));
	pFLay->addRow(m_TimeLapse.ProvideNewLabel(theDeviceWidget), m_TimeLapse.ProvideNewParamSpinBox(theDeviceWidget));

	pFLay->addRow(m_Output.ProvideNewLabel(theDeviceWidget), m_Output.ProvideNewParamSpinBox(theDeviceWidget));
	// We add the reset button, once again by asking the GParamBool to provide its own button interface.
	pVlay->addWidget(m_Reset.ProvideNewParamButton(theDeviceWidget));
	// We add an expandable space.
	pVlay->addStretch();
}
//[PopulateDeviceWidgetImplementation]

void GLowPassFilter::Reset()
{
	m_History.clear();
	// Send the input right to the output since it is the only value we have
	m_Output = m_InputBucket.DoubleValue();

	// should we do time lapse now?
	m_LapseTimer.stop();
	if(m_DoTimeLapse && m_TimeLapse) {
		m_LapseTimer.setInterval(1000 * m_TimeLapse);
		m_LapseTimer.start();
	}
	else {

	}
}

void GLowPassFilter::EventSampleArrived(double newValue)
{
	// prepends the new data to the beginning of the list
	m_History.prepend(newValue);

	// if time lapse, we take as many data as needed and the timer will do the UpdateOutput()
	if(m_DoTimeLapse && m_TimeLapse) {
		return;
	}

	// quick way to implement the history by removing the unused parameters
	int maxSize = qMax(1, m_SampleSize.IntValue());
	while(m_History.count() > maxSize) {
		m_History.removeLast();
	}

	// launches the average calculation and update the output
	UpdateOutput();
}

void GLowPassFilter::UpdateOutput()
{
	// best way would be to throw exception if the average doesn't make sense
	int NValuesToConsider = qMax(1, m_SampleSize.IntValue());

	int numValueSummed = 0;
	double average = 0.0;
	// we average until we have enough samples
	foreach(double val, m_History) {
		average += val;
		numValueSummed++;
		if(numValueSummed == NValuesToConsider)
			break;
	}
	if(numValueSummed == 0)
		return;
	m_Output = average / double(numValueSummed);

	// if time lapse, we clear the history
	if(m_DoTimeLapse && m_TimeLapse) {
		m_History.clear();
	}
}






