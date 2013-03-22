#include "GRandomNumberGenerator.h"

GRandomNumberGenerator::GRandomNumberGenerator(QObject *parent, QString uniqueIdentifierName /* = "" */)
	: GProgDevice(parent, uniqueIdentifierName)
	, m_Seed("seed", this)
	, m_MaxUniformValue("max", this)
	, m_LastOut("out", this, GParam::ReadOnly)
	, m_DoGenerate("Generate", this)
	, m_pTimer(0)
{
	// put initialization code here
	m_MaxUniformValue = 1.0;

	// makes the seed update
	SetSeed();
	connect(&m_Seed, SIGNAL(ValueUpdated(double)), this, SLOT(SetSeed()));

	connect(&m_DoGenerate, SIGNAL(ValueUpdated(bool)), this, SLOT(Activate(bool)));
}

GRandomNumberGenerator::~GRandomNumberGenerator()
{

}

void GRandomNumberGenerator::PopulateDeviceWidget(GDeviceWidget* theDeviceWidget )
{
	QVBoxLayout* pVLay = new QVBoxLayout();
	theDeviceWidget->AddSubLayout(pVLay);
	// a form layout
 	QFormLayout* pLay = new QFormLayout();
	pVLay->addLayout(pLay);
	// add the parameters' labels and spinboxes
	pLay->addRow(m_Seed.ProvideNewLabel(theDeviceWidget), m_Seed.ProvideNewParamSpinBox(theDeviceWidget));
	pLay->addRow(m_MaxUniformValue.ProvideNewLabel(theDeviceWidget), m_MaxUniformValue.ProvideNewParamSpinBox(theDeviceWidget));
	pLay->addRow(m_LastOut.ProvideNewLabel(theDeviceWidget), m_LastOut.ProvideNewParamSpinBox(theDeviceWidget));

	pVLay->addWidget(m_DoGenerate.ProvideNewParamButton(theDeviceWidget));
	pVLay->addStretch(50);
}

double GRandomNumberGenerator::GenerateRandom()
{
	m_LastOut = double(qrand()) / double(RAND_MAX) * m_MaxUniformValue;
	return m_LastOut;
}

void GRandomNumberGenerator::SetSeed()
{
	qsrand(m_Seed);
}

void GRandomNumberGenerator::Activate(bool doGenerate)
{
	if(doGenerate) {
		m_pTimer = new QTimer(this);
		connect(m_pTimer, SIGNAL(timeout()), this, SLOT(GenerateRandom()));
		m_pTimer->start(10);
	}
	else if(m_pTimer) {
		delete m_pTimer;
		m_pTimer = 0;
	}
}