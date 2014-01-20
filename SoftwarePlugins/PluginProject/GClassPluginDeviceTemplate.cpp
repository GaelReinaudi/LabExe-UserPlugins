#include "GClassPluginDeviceTemplate.h"

GClassPluginDeviceTemplate::GClassPluginDeviceTemplate(QObject *parent, QString uniqueIdentifierName /* = "" */)
	: GProgDevice(parent, uniqueIdentifierName)
	, m_MyNumber("iterations", this)
	, m_MyDouble("speed", this, GParam::ReadOnly)
{
	// put initialization code here
}

GClassPluginDeviceTemplate::~GClassPluginDeviceTemplate()
{

}

void GClassPluginDeviceTemplate::PopulateDeviceWidget(GDeviceWidget* theDeviceWidget )
{
 	QFormLayout* pLay = new QFormLayout();
	theDeviceWidget->AddSubLayout(pLay);
	pLay->addRow(m_MyNumber.ProvideNewLabel(theDeviceWidget), m_MyNumber.ProvideNewParamSpinBox(theDeviceWidget));
	pLay->addRow(m_MyDouble.ProvideNewLabel(theDeviceWidget), m_MyDouble.ProvideNewParamSpinBox(theDeviceWidget));
}
