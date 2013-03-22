#include "GMonteCarloLogNormalPricerWidget.h"
#include "GMonteCarloLogNormalPricer.h"

GMonteCarloLogNormalPricerWidget::GMonteCarloLogNormalPricerWidget(GMonteCarloLogNormalPricer* pPricer, QWidget *parent /*= 0*/)
	: QWidget(parent)
	, m_pPricer(pPricer)
{
	setupUi(this);

	QComboBox* pComboPay = m_pPricer->m_PayOffType.ProvideNewParamComboBox(this, QStringList() << "European Call" << "Digital Call" << "Equation");
	pPayLay->insertWidget(0, pComboPay);
	connect(pComboPay, SIGNAL(currentIndexChanged(int)), pPayOffStackWidget, SLOT(setCurrentIndex(int)));
	pFormStrike1->addWidget(m_pPricer->m_StrikeBucket.ProvideParamBucketTreeWidget(this));
	pFormStrike2->addWidget(m_pPricer->m_StrikeBucket.ProvideParamBucketTreeWidget(this));
	pLayoutEquation->addWidget(m_pPricer->m_EquationString.ProvideNewParamLineEdit(this));

	// We insert a widget provided by the input param bucket.
	pVlay->addWidget(m_pPricer->m_ExpiryBucket.ProvideParamBucketTreeWidget(this));
	pVlay->addWidget(m_pPricer->m_VolBucket.ProvideParamBucketTreeWidget(this));

	// We add a form layout that will hold the numerical settings.
	QFormLayout* pFLay = new QFormLayout();
	pVlay->addLayout(pFLay);
	// We add the parameter labels and spinboxes by using the convenient function from the GParam class
	pFLay->addRow(m_pPricer->m_InterestRate.ProvideNewLabel(this), m_pPricer->m_InterestRate.ProvideNewParamSpinBox(this));
	pFLay->addRow(m_pPricer->m_PathNumber.ProvideNewLabel(this), m_pPricer->m_PathNumber.ProvideNewParamSpinBox(this));
	// We add the reset and run button
	QPushButton* pRunButton = m_pPricer->m_Run.ProvideNewParamButton(this);
	pRunButton->setCheckable(true);
	pFLay->addRow(m_pPricer->m_Reset.ProvideNewParamButton(this), pRunButton);
	// the output value that will hack a plotting widget to do the plotting
	pVlay->addWidget(m_pPricer->m_OutputBridgeToEmitManyValues.ProvideNewLabel(this));
	pVlay->addWidget(m_pPricer->m_OutputBridgeToEmitManyValues.ProvideNewParamSpinBox(this));
	// We add an expandable space.
	pVlay->addStretch(10);
}

GMonteCarloLogNormalPricerWidget::~GMonteCarloLogNormalPricerWidget()
{

}
