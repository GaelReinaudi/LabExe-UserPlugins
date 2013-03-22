#include "GBasicParamSwitcher.h"

GBasicParamSwitcher::GBasicParamSwitcher(QObject *parent, QString uniqueIdentifierName /*= ""*/)
	: GProgDevice(parent, uniqueIdentifierName)
	, m_BucketParam("Switched", this)
	, m_BucketTrigger("Trigger", this)
	, m_FirstValue("1", this)
	, m_SecValue("2", this)
{
	connect(&m_BucketTrigger, SIGNAL(ValueUpdated(double)), this, SLOT(Switch()), Qt::QueuedConnection);
}

GBasicParamSwitcher::~GBasicParamSwitcher()
{

}

void GBasicParamSwitcher::PopulateDeviceWidget(GDeviceWidget* theDeviceWidget )
{
	QBoxLayout* pVLay0 = new QVBoxLayout();
	theDeviceWidget->AddSubLayout(pVLay0);

	QWidget* pWidTrigg = m_BucketTrigger.ProvideNewParamWidget(theDeviceWidget);
	pVLay0->addWidget(pWidTrigg); 

	QBoxLayout* pHLay = new QHBoxLayout();
	pVLay0->addLayout(pHLay);

	QBoxLayout* pVLay = new QVBoxLayout();
	QBoxLayout* pVLay2 = new QVBoxLayout();
	pHLay->addLayout(pVLay);
	pHLay->addLayout(pVLay2);

	QWidget* pWidSwitch = m_BucketParam.ProvideNewParamWidget(theDeviceWidget);
	pVLay->addWidget(pWidSwitch);

	QWidget* pFirstValueWid = m_FirstValue.ProvideNewParamSpinBox(theDeviceWidget);
	pVLay2->addWidget(pFirstValueWid); 
	QWidget* pSecValueWid = m_SecValue.ProvideNewParamSpinBox(theDeviceWidget);
	pVLay2->addWidget(pSecValueWid);

	pVLay->addStretch();
	pVLay2->addStretch();
	pVLay0->addStretch();
}

void GBasicParamSwitcher::Switch()
{
	GParamNum* pTrig = m_BucketTrigger.ParamNum();
	GParamNum* pSwi = m_BucketParam.ParamNum();
	if(!pTrig || !pSwi)
		return;
	int valTrig = pTrig->IntValue();
	if(valTrig % 2 != 0)
		pSwi->SetParamValue(m_SecValue.DoubleValue());
	else
		pSwi->SetParamValue(m_FirstValue.DoubleValue());
}