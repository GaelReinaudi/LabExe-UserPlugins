#include "GLockingSlapper.h"

GLockingSlapper::GLockingSlapper(QObject *parent, QString uniqueIdentifierName /* = "" */)
	: GProgDevice(parent, uniqueIdentifierName)
	, m_SetPointBucket("Set-point", this)
	, m_InputBucket("Input", this)
	, m_OutputBucket("Output", this)
	, m_Gain("Gain", this)
	, m_MaxSlapSize("Max. slap size", this)
	, m_ErrorSignal("Error signal", this, GParam::ReadOnly)
	, m_Enable("Enable", this)
{
	// Default value of the sample size for the first use.
	// It will be over-written if a previously saved value is read from a file.
	m_Gain.SetHardLimits(-1000, 1e6);
	m_Gain.SetDisplayDecimals(2);
	m_ErrorSignal.SetHardLimits(-1e6, 1e6);
	m_ErrorSignal.SetDisplayDecimals(2);
	m_MaxSlapSize.SetDisplayDecimals(2);

	m_Gain = 0.1;
	m_MaxSlapSize = 0.1;

	connect(&m_InputBucket, SIGNAL(ValueUpdated(double)), this, SLOT(Iteration()));
	connect(&m_SetPointBucket, SIGNAL(ValueUpdated(double)), this, SLOT(Iteration()));
}

GLockingSlapper::~GLockingSlapper()
{

}

/////////////////////////////////////////////////////////////////////
/*!
Populates a widget provided by a workbench in order to represent (and be adequately connected to) this GLockingSlapper. 
Layouts are used to make the widget react correctly to re-sizing.
The easiest way to connect the button and spinboxes to the actual instance of the corresponding parameter 
is to use the method GParamXXXX::ProvideNew----Widget(), that does all the necessary connections 
automatically (which would be the equivalent of this PopulateDeviceWidget(), but for a single parameter).
\param:  GDeviceWidget * theDeviceWidget : the parent widget in the gui.
*////////////////////////////////////////////////////////////////////

void GLockingSlapper::PopulateDeviceWidget(GDeviceWidget* theDeviceWidget )
{
	// We add a vertical layout to hold together all the widgets that we are going to display.
	QVBoxLayout* pVlay = new QVBoxLayout();
	theDeviceWidget->AddSubLayout(pVlay);
	// We insert a widget provided by the input param bucket.
	pVlay->addWidget(m_InputBucket.ProvideNewParamWidget(theDeviceWidget));
	pVlay->addWidget(m_SetPointBucket.ProvideNewParamWidget(theDeviceWidget));
	// We add a form layout that will hold the numerical settings.
 	QFormLayout* pFLay = new QFormLayout();
	pVlay->addLayout(pFLay);
	// We add the parameter labels and spinboxes by using the convenient function from the GParam class
	pFLay->addRow(m_ErrorSignal.ProvideNewLabel(theDeviceWidget), m_ErrorSignal.ProvideNewParamSpinBox(theDeviceWidget));
	pFLay->addRow(m_Gain.ProvideNewLabel(theDeviceWidget), m_Gain.ProvideNewParamSpinBox(theDeviceWidget));
	pFLay->addRow(m_MaxSlapSize.ProvideNewLabel(theDeviceWidget), m_MaxSlapSize.ProvideNewParamSpinBox(theDeviceWidget));
	// We add the reset button, once again by asking the GParamBool to provide its own button interface.
	pVlay->addWidget(m_Enable.ProvideNewParamCheckBox(theDeviceWidget));
	pVlay->addWidget(m_OutputBucket.ProvideNewParamWidget(theDeviceWidget));
	// We add an expandable space.
	pVlay->addStretch();
}

void GLockingSlapper::Iteration()
{
	if(m_InputBucket.IsEmpty() || m_OutputBucket.IsEmpty())
		return;
	double currentInput = m_InputBucket.DoubleValue();
	double currentOutput = m_OutputBucket.DoubleValue();
	double setpoint = m_SetPointBucket.DoubleValue();

	// temp
	if(currentInput <= 0)
		return;

	if(!m_Enable)
		return;

	double errorSignal = currentInput - setpoint;
	m_ErrorSignal = errorSignal;

// 	if(errorSiganl > + 0.001)
// 		currentOutput += 0.01;
// 	if(errorSiganl < - 0.001)
// 		currentOutput -= 0.01;
// 	if(errorSiganl > + 0.0001)
// 		currentOutput += 0.001;
// 	if(errorSiganl < - 0.0001)
// 		currentOutput -= 0.001;
// 	if(errorSiganl > + 0.00001)
// 		currentOutput += 0.0001;
// 	if(errorSiganl < - 0.00001)
// 		currentOutput -= 0.0001;
	const double maxVariationPerIteration = m_MaxSlapSize;
	double VariOutput = errorSignal * m_Gain;
	VariOutput = qMin(qMax(- maxVariationPerIteration, VariOutput), maxVariationPerIteration);

	currentOutput += VariOutput;

	m_OutputBucket.SetParamValue(currentOutput);
}
