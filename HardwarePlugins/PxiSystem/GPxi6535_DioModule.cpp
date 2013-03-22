#include "GPxi6535_DioModule.h"
#include "GPxiBasicDigitalOutput.h"

GPxi6535_DioModule::GPxi6535_DioModule(QString NiDeviceName, QObject *parent)
	: GHardDevice(NiDeviceName, parent)
	, GDAQmxModule(NiDeviceName)
{
	CreateSubDevicesChannels();
}

GPxi6535_DioModule::~GPxi6535_DioModule()
{

}

void GPxi6535_DioModule::CreateSubDevicesChannels()
{
	QStringList listStrDo = NiToQString(NiDevice().GetPhysicalChannels(DAQmxPhysicalChannelTypeDOLine, DAQmxPhysicalChannelAccessExternal));
	QStringList listStrDi = NiToQString(NiDevice().GetPhysicalChannels(DAQmxPhysicalChannelTypeDILine, DAQmxPhysicalChannelAccessExternal));
	foreach(QString str, listStrDo) {
		GPxiBasicDigitalOutput* thenewChan = new GPxiBasicDigitalOutput(str, this);
		m_ListDO.append(thenewChan);
	}
}

void GPxi6535_DioModule::PopulateDeviceWidget(GDeviceWidget* theDeviceWidget )
{
// 	if(!IsValid())
// 		return;
// 
// 	// layout (in a groupbox) for the digital outputs
// 	QFormLayout* DoFormLayout = new QFormLayout();
// 	theDeviceWidget->AddSubGroupBox("Digital outputs", DoFormLayout);
// 	// a combo to drag and drop the subdevices in the lab
// 	QComboBox* pComboDo = new QComboBox(theDeviceWidget);
// 	pComboDo->view()->setDragDropMode(QAbstractItemView::DragOnly);
// 	pComboDo->setModel(new GDeviceListModel(pComboDo));
// 	// Let's populate the combo with names and the pointer to the corresponding GDevice's. (We use QVariant for that).
// 	foreach(GDevice* pDev, m_ListDO) {
// 		pComboDo->addItem(pDev->Name(), QVariant::fromValue(pDev->UniqueSystemID()));
// 	}
// 
// 	DoFormLayout->addRow(tr("D&O:"), pComboDo);
}

QList<GDevice*> GPxi6535_DioModule::SubDevices() const
{
	return m_ListDO;
}