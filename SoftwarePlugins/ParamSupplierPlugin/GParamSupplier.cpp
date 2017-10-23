#include "GParamSupplier.h"

//! [Initialize the parameters]
GParamSupplier::GParamSupplier(QObject *parent, QString uniqueIdentifierName /* = "" */)
	: GProgDevice(parent, uniqueIdentifierName)
	, m_InputBucket("input", this)
	, m_SuppliedBucket("supplied", this)
	, m_ActiveParamIndex("index", this)
	, m_DoWrap("wrap", this)
	, m_AbsoluteSupply("absolute", this)
	, m_DoBinary("bit-wise selection", this)
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
	m_ActiveParamIndex.SetParamValue(0);
	m_ActiveParamIndex.DefaultParam()->SetHardLimits(-1, 1e6);
	m_ActiveParamIndex.DefaultParam()->SetTypicalStep(1);
	m_ActiveParamIndex.DefaultParam()->SetDisplayDecimals(0);

	m_InputBucket.RemoveExtraField("trig");
	m_ActiveParamIndex.RemoveExtraField("trig");
	m_SuppliedBucket.RemoveExtraField("trig");
	m_SuppliedBucket.AddExtraFieldBool("sel");

	// Connects the input bucket to the event that starts a calculation of the average
	connect(&m_InputBucket, SIGNAL(ValueDidChange(double)), this, SLOT(EventSampleArrived(double)));
	// if index changes
	connect(&m_ActiveParamIndex, SIGNAL(ValueUpdated(double)), this, SLOT(ChangeSelection()));

	connect(&m_DoWrap, SIGNAL(ValueUpdated(bool)), this, SLOT(ChangeSelection()), Qt::QueuedConnection);
	connect(&m_AbsoluteSupply, SIGNAL(ValueUpdated(bool)), this, SLOT(ChangeSelection()), Qt::QueuedConnection);
	connect(&m_DoBinary, SIGNAL(ValueUpdated(bool)), this, SLOT(ChangeSelection()), Qt::QueuedConnection);
}
//! [Extra initialization the parameters]

GParamSupplier::~GParamSupplier()
{

}

/////////////////////////////////////////////////////////////////////
/*!
Populates a widget provided by a workbench in order to represent (and be adequately connected to) this GParamSupplier. 
Layouts are used to make the widget react correctly to re-sizing.
The easiest way to connect the button and spinboxes to the actual instance of the corresponding parameter 
is to use the method GParamXXXX::ProvideNew----Widget(), that does all the necessary connections 
automatically (which would be the equivalent of this PopulateDeviceWidget(), but for a single parameter).
\param:  GDeviceWidget * theDeviceWidget : the parent widget in the gui.
*////////////////////////////////////////////////////////////////////
//[PopulateDeviceWidgetImplementation]
void GParamSupplier::PopulateDeviceWidget(GDeviceWidget* theDeviceWidget )
{
	// We add layouts to hold together all the widgets that we are going to display.
	QVBoxLayout* pVlayLeft = new QVBoxLayout();
	QVBoxLayout* pVlayRight = new QVBoxLayout();
	QHBoxLayout* pHlay = new QHBoxLayout();
	pHlay->addLayout(pVlayLeft);
	pHlay->addLayout(pVlayRight);
	theDeviceWidget->AddSubLayout(pHlay);

	// We insert a widget provided by the input param bucket.
	pVlayLeft->addWidget(m_InputBucket.ProvideNewParamWidget(theDeviceWidget));
	// We add a form layout that will hold some settings.
 	QFormLayout* pFLay = new QFormLayout();
	pVlayLeft->addLayout(pFLay);
	pFLay->addRow(m_AbsoluteSupply.ProvideNewLabel(theDeviceWidget), m_AbsoluteSupply.ProvideNewParamCheckBox(theDeviceWidget, ""));
	pFLay->addRow(m_DoWrap.ProvideNewLabel(theDeviceWidget), m_DoWrap.ProvideNewParamCheckBox(theDeviceWidget, ""));
	pFLay->addRow(m_DoBinary.ProvideNewLabel(theDeviceWidget), m_DoBinary.ProvideNewParamCheckBox(theDeviceWidget, ""));

	// We add the parameter labels and spinboxes by using the convenient function from the GParam class
	pVlayLeft->addWidget(m_ActiveParamIndex.ProvideNewParamWidget(theDeviceWidget));
	// We add an expandable space.
	pVlayLeft->addStretch();

	pVlayRight->addWidget(m_SuppliedBucket.ProvideNewParamWidget(theDeviceWidget));
}
//[PopulateDeviceWidgetImplementation]

void GParamSupplier::EventSampleArrived(double newValue)
{
    Q_UNUSED(newValue);
	UpdateOutput();
}

void GParamSupplier::UpdateOutput()
{
	// get all the param that have a "sel" field checked
	QVector<bool> maskSel = m_SuppliedBucket.ExtraParamBoolMask("sel");
	QVector<GParamNum*> selectedParam = m_SuppliedBucket.ParamNums(maskSel);
	// if we do the absolute transfer sends the value to those.
	if(m_AbsoluteSupply) {
		foreach(GParamNum* pPar, selectedParam) {
			pPar->SetParamValue(m_InputBucket.DoubleValue());
		}
	} // else, it is a relative move so we add up only the part that changed since the last selection change
	else {
		double currentIn = m_InputBucket.DoubleValue();
		double delta = currentIn - m_lastInUpdate;
		foreach(GParamNum* pPar, selectedParam) {
			(*pPar) += delta;
		}
		m_lastInUpdate = currentIn;
	}
}

void GParamSupplier::ChangeSelection()
{
	// resets the relative change of the input
	m_lastInUpdate = m_InputBucket.DoubleValue();

	int selToBe = qRound(m_ActiveParamIndex.DoubleValue());
	int paramCount = m_SuppliedBucket.ParamCount();
	// if wrap, we ensure it is valid index (unless it is a binary representation)
	if(m_DoWrap && !m_DoBinary) {
		selToBe %= paramCount;
	}
//	// if negative, we return
// 	if(selToBe < 0)
// 		return;
// 	// if not a binary representation, we don't do anything if it falls out of range
// 	if(!m_DoBinary && selToBe >= paramCount)
// 		return;

	// Make the mask of "sel" by using the selToBe
	QVector<bool> toSelect(paramCount);
	if(m_DoBinary) { // for binary, it is the binary representation of the 
		for(int i = 0; i < paramCount ; i++) {
			toSelect[i] = ((1 << i) & selToBe);
		}
	}
	else { // else, just one of them can be true
		for(int i = 0; i < paramCount ; i++) {
			toSelect[i] = (i == selToBe);
		}
	}
	// get the "sel" bool param for the bucket
	QVector<GParamBool*> parBools = m_SuppliedBucket.ExtraParams<GParamBool>("sel");
	int i = -1;
	foreach(GParamBool* pB, parBools) {
		++i;
		pB->SetParamValue(toSelect[i]);
	}

	UpdateOutput();
}








