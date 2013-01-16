#include "GPxi6713_AoModule.h"
#include "GPxiBasicAnalogOutput.h"

GPxi6713_AoModule::GPxi6713_AoModule(QString NiDeviceName, QObject *parent)
	: GHardDevice(NiDeviceName, parent)
	, GDAQmxModule(NiDeviceName)
{
	CreateSubDevicesChannels();
}

GPxi6713_AoModule::~GPxi6713_AoModule()
{

}

void GPxi6713_AoModule::CreateSubDevicesChannels()
{
	QStringList listStrAo = NiToQString(NiDevice().GetPhysicalChannels(DAQmxPhysicalChannelTypeAO, DAQmxPhysicalChannelAccessExternal));
	foreach(QString str, listStrAo) {
		GPxiBasicAnalogOutput* thenewChan = new GPxiBasicAnalogOutput(str, this);
		m_ListAO.append(thenewChan);
	}
}

void GPxi6713_AoModule::PopulateDeviceWidget(GDeviceWidget* theDeviceWidget )
{
// 	if(!IsValid())
// 		return;
// 
// 	// layout (in a groupbox) for the analog outputs
// 	QFormLayout* AoFormLayout = new QFormLayout();
// 	theDeviceWidget->AddSubGroupBox("Analog outputs", AoFormLayout);
// 	// a combo to drag and drop the subdevices in the lab
// 	QComboBox* pComboAo = new QComboBox(theDeviceWidget);
// 	pComboAo->view()->setDragDropMode(QAbstractItemView::DragOnly);
// 	pComboAo->setModel(new GDeviceListModel(pComboAo));
// 	// Let's populate the combo with names and the pointer to the corresponding GDevice's. (We use QVariant for that).
// 	foreach(GDevice* pDev, m_ListAO) {
// 		pComboAo->addItem(pDev->Name(), QVariant::fromValue(pDev->UniqueSystemID()));
// 	}
// 
// 	AoFormLayout->addRow(tr("A&O:"), pComboAo);
}
