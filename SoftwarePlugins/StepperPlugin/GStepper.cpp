#include "GStepper.h"

//! [Initialize the parameters]
GStepper::GStepper(QObject *parent, QString uniqueIdentifierName /* = "" */)
	: GProgDevice(parent, uniqueIdentifierName)
	, m_InputBucket("Trigger", this)
	, m_OutputBucket("Output", this)
	, m_Reset("Reset", this)
	, m_Enable("Enable Sweep", this)
	, m_Start("Start", this)
	, m_StepSize("Step Size", this)
	, m_Maximum("Maximum", this)
	, m_Delay("Delay (s)", this)
	, m_Steps("Number of Points", this, GParam::ReadOnly)
	, m_CurrentStep("Current Point", this, GParam::ReadOnly)
	, m_PointsPerStep("Points Per Step", this)
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
	m_StepSize.SetHardLimits(0.0, 99.9);
	m_StepSize.SetDisplayDecimals(3);

// 	m_PointsPerStep = 1;
	m_PointsPerStep.SetHardLimits(1, 1000000);

	m_Delay.SetTypicalStep(0.01);
	m_Delay.SetHardLimits(0.00, 99.9);

	m_Start.SetDisplayDecimals(2);
	m_Maximum.SetDisplayDecimals(2);

	// Connects the input bucket to the event that starts a calculation of the average
	connect(&m_InputBucket, SIGNAL(ValueUpdated(double)), this, SLOT(StartUpdateOutput()));
	// Connects the \e reset parameter to the function that does Reset() the average.

	connect(&m_Reset, SIGNAL(ValueUpdated(bool)), this, SLOT(Reset()));
	connect(&m_Start, SIGNAL(ValueUpdated(double)), this, SLOT(Reset()));
	connect(&m_Maximum, SIGNAL(ValueUpdated(double)), this, SLOT(Reset()));
	connect(&m_StepSize, SIGNAL(ValueUpdated(double)), this, SLOT(Reset()));
	connect(&m_PointsPerStep, SIGNAL(ValueUpdated(double)), this, SLOT(Reset()));
	
	connect(&m_PointsPerStep, SIGNAL(ValueUpdated(double)), this, SLOT(SetSteps()));
	connect(&m_StepSize, SIGNAL(ValueUpdated(double)), this, SLOT(SetSteps()));
	connect(&m_Maximum, SIGNAL(ValueUpdated(double)), this, SLOT(SetSteps()));
	connect(&m_Start, SIGNAL(ValueUpdated(double)), this, SLOT(SetSteps()));
}
//! [Extra initialization the parameters]

GStepper::~GStepper()
{

}

/////////////////////////////////////////////////////////////////////
/*!
Populates a widget provided by a workbench in order to represent (and be adequately connected to) this GStepper. 
Layouts are used to make the widget react correctly to re-sizing.
The easiest way to connect the button and spinboxes to the actual instance of the corresponding parameter 
is to use the method GParamXXXX::ProvideNew----Widget(), that does all the necessary connections 
automatically (which would be the equivalent of this PopulateDeviceWidget(), but for a single parameter).
\param:  GDeviceWidget * theDeviceWidget : the parent widget in the gui.
*////////////////////////////////////////////////////////////////////
//[PopulateDeviceWidgetImplementation]


void GStepper::PopulateDeviceWidget(GDeviceWidget* theDeviceWidget )
{
	// We add a vertical layout to hold together all the widgets that we are going to display.
	QVBoxLayout* pVlay = new QVBoxLayout();
	theDeviceWidget->AddSubLayout(pVlay);
	// We insert a widget provided by the input param bucket.
	pVlay->addWidget(m_InputBucket.ProvideNewParamWidget(theDeviceWidget));
	pVlay->addWidget(m_OutputBucket.ProvideNewParamWidget(theDeviceWidget));
	// We add a form layout that will hold the numerical settings.
 	QFormLayout* pFLay = new QFormLayout();
	pVlay->addLayout(pFLay);
	// We add the parameter labels and spinboxes by using the convenient function from the GParam class
	pFLay->addRow(m_Delay.ProvideNewLabel(theDeviceWidget), m_Delay.ProvideNewParamSpinBox(theDeviceWidget));
	pFLay->addRow(m_Start.ProvideNewLabel(theDeviceWidget), m_Start.ProvideNewParamSpinBox(theDeviceWidget));
	pFLay->addRow(m_Maximum.ProvideNewLabel(theDeviceWidget), m_Maximum.ProvideNewParamSpinBox(theDeviceWidget));
	pFLay->addRow(m_StepSize.ProvideNewLabel(theDeviceWidget), m_StepSize.ProvideNewParamSpinBox(theDeviceWidget));
	pFLay->addRow(m_Steps.ProvideNewLabel(theDeviceWidget), m_Steps.ProvideNewParamSpinBox(theDeviceWidget));
	pFLay->addRow(m_CurrentStep.ProvideNewLabel(theDeviceWidget), m_CurrentStep.ProvideNewParamSpinBox(theDeviceWidget));
	pFLay->addRow(m_PointsPerStep.ProvideNewLabel(theDeviceWidget), m_PointsPerStep.ProvideNewParamSpinBox(theDeviceWidget));
	// We add the reset button, once again by asking the GParamBool to provide its own button interface.
	pVlay->addWidget(m_Reset.ProvideNewParamButton(theDeviceWidget));
	pVlay->addWidget(m_Enable.ProvideNewParamCheckBox(theDeviceWidget));
	// We add an expandable space.
	pVlay->addStretch();
}
//[PopulateDeviceWidgetImplementation]

void GStepper::SetSteps()//Calculates # of steps in the sweep
{
	int ppsteps = qMax(1, m_PointsPerStep.IntValue());
	m_Steps = ppsteps * (floor(abs(((m_Maximum - m_Start) / m_StepSize))) + 1);
}

void GStepper::StartUpdateOutput()//This function exists in order to allow a user-input delay
{								//between the trigger and the update of the output.  Only called
	if(m_Delay > 0.0)			//when there is a nonzero delay.
		QTimer::singleShot(int(m_Delay * 1000), this, SLOT(UpdateOutput()));
	else
		UpdateOutput();
}

void GStepper::UpdateOutput()
{
	int ppsteps = qMax(1, m_PointsPerStep.IntValue());
	if(m_Enable)//Only updates output if the "Enable Sweep" checkbox is checked
	{
		if (m_Maximum > m_Start)//If you're counting up...
		{
			if (m_CurrentFreq <= m_Maximum - m_StepSize * 0.999999999999)//The 0.9999... is to
				//ensure that a rounding error doesn't cause (m_Maximum - m_StepSize) to be 
				//artificially small, and therefore prevent this condition from being executed.
			{
				if (m_CurrentStep.IntValue() % ppsteps == 0)
				{
					//Recall that m_StepSize is forced to be positive.
					m_CurrentFreq = m_Start + m_CurrentStep * m_StepSize / ppsteps;
					m_OutputBucket.SetParamValue(m_CurrentFreq);
				}
					m_CurrentStep += 1;
			}
			else
			{
				m_CurrentFreq = m_Start;
				m_CurrentStep = 1;
				m_OutputBucket.SetParamValue(m_CurrentFreq);
			}
		}
		else//If you're counting down...
		{
			if (m_CurrentFreq >= m_Maximum + m_StepSize * 0.999999999999)
			{
				if (m_CurrentStep.IntValue() % ppsteps == 0)
				{
					m_CurrentFreq = m_Start - m_CurrentStep * m_StepSize / ppsteps;
					m_OutputBucket.SetParamValue(m_CurrentFreq);
				}
				m_CurrentStep += 1;
			}
			else
			{
				m_CurrentFreq = m_Start;
				m_CurrentStep = 1;
				m_OutputBucket.SetParamValue(m_CurrentFreq);
			}
		}
	}
}

void GStepper::Reset()
{
	m_OutputBucket.SetParamValue(m_Start);
	m_CurrentFreq = m_Start;
	m_CurrentStep = 1;
}