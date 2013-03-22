#include "GPxi6229_AiModule.h"
#include "GPxiBasicAnalogInput.h"

GPxi6229_AiModule::GPxi6229_AiModule(QString NiDeviceName, QObject *parent)
	: GHardDevice(NiDeviceName, parent)
	, GDAQmxModule(NiDeviceName)
{
	CreateSubDevicesChannels();
}

GPxi6229_AiModule::~GPxi6229_AiModule()
{

}

QList<GDevice*> GPxi6229_AiModule::SubDevices() const
{
	return m_ListAI;
}

void GPxi6229_AiModule::CreateSubDevicesChannels()
{
	QStringList listStrAi = NiToQString(NiDevice().GetPhysicalChannels(DAQmxPhysicalChannelTypeAI, DAQmxPhysicalChannelAccessExternal));
	foreach(QString str, listStrAi) {
		GPxiBasicAnalogInput* thenewChan = new GPxiBasicAnalogInput(str, this);
		m_ListAI.append(thenewChan);
	}
}

void GPxi6229_AiModule::PopulateDeviceWidget(GDeviceWidget* theDeviceWidget )
{
// 	if(!IsValid())
// 		return;
// 
// 	// layout (in a groupbox) for the analog outputs
// 	QFormLayout* AiFormLayout = new QFormLayout();
// 	theDeviceWidget->AddSubGroupBox("Analog inputs", AiFormLayout);
// 	// a combo to drag and drop the subdevices in the lab
// 	QComboBox* pComboAi = new QComboBox(theDeviceWidget);
// 	pComboAi->view()->setDragDropMode(QAbstractItemView::DragOnly);
// 	pComboAi->setModel(new GDeviceListModel(pComboAi));
// 
// 	// Let's populate the combo with names and the pointer to the corresponding GDevice's. (We use QVariant for that).
// 	foreach(GDevice* pDev, m_ListAI)
// 		pComboAi->addItem(pDev->Name(), QVariant::fromValue(pDev->UniqueSystemID()));
// 
// 	AiFormLayout->addRow(tr("A&I:"), pComboAi);
}

