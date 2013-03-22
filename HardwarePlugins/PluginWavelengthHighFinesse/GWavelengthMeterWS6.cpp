#include "GWavelengthMeterWS6.h"
#include "GWS6Channel.h"

G_REGISTER_HARD_DEVICE_CLASS(GWavelengthMeterWS6)

GWavelengthMeterWS6::GWavelengthMeterWS6(QString uniqueIdentifierName, QObject *parent)
	: GHardDevice(uniqueIdentifierName, parent)
{
	Instantiate(cInstNotification, cNotifyInstallWaitEvent, 1000, 0);

	CreateSubDevicesChannels();
	EnableWLMonitoring(true);
}

GWavelengthMeterWS6::~GWavelengthMeterWS6()
{
	EnableWLMonitoring(false);
	wait(1500);
	Instantiate(cInstNotification, cNotifyRemoveWaitEvent, 0, 0);
}

void GWavelengthMeterWS6::run()
{
	//change the priority of the thread to not take resources from the rest of the program
	setPriority(QThread::LowPriority);
	long whatChanged = 0;
	long intVal = 0;
	double dblVal = 0.0;
	// start looping
	m_ThreadWaitForEvents = true;
	while(m_ThreadWaitForEvents){ // keeps looping as long as m_ThreadWaitForEvents is true
		// get the first pending event in the WS6
		int ret = WaitForWLMEvent(whatChanged, intVal, dblVal);
		// in the case it is a channel with a wavelength changed we call the corresponding channel object update function.
		GWS6Channel* pChan = 0;
		switch(whatChanged) {
		case cmiWavelength1:
			pChan = qobject_cast<GWS6Channel*>(m_Channels.value(0));
			if(pChan)
				pChan->IncomingUpdate(dblVal);
			break;
		case cmiWavelength2:
			pChan = qobject_cast<GWS6Channel*>(m_Channels.value(1));
			if(pChan)
				pChan->IncomingUpdate(dblVal);
			break;
		case cmiWavelength3:
			pChan = qobject_cast<GWS6Channel*>(m_Channels.value(2));
			if(pChan)
				pChan->IncomingUpdate(dblVal);
			break;
		case cmiWavelength4:
			pChan = qobject_cast<GWS6Channel*>(m_Channels.value(3));
			if(pChan)
				pChan->IncomingUpdate(dblVal);
			break;
		case cmiWavelength5:
			pChan = qobject_cast<GWS6Channel*>(m_Channels.value(4));
			if(pChan)
				pChan->IncomingUpdate(dblVal);
			break;
		case cmiWavelength6:
			pChan = qobject_cast<GWS6Channel*>(m_Channels.value(5));
			if(pChan)
				pChan->IncomingUpdate(dblVal);
			break;
		case cmiWavelength7:
			pChan = qobject_cast<GWS6Channel*>(m_Channels.value(6));
			if(pChan)
				pChan->IncomingUpdate(dblVal);
			break;
		case cmiWavelength8:
			pChan = qobject_cast<GWS6Channel*>(m_Channels.value(7));
			if(pChan)
				pChan->IncomingUpdate(dblVal);
			break;
		}

		// completely arbitrary choice of sleeping time! 
		// depending on what was detected and if some more is waiting to be detected
		switch(ret) {
		case 1: // if there are other measurement waiting to be queried
			msleep(1);
			break;
		case 2: // if no other measurement waiting to be queried
			msleep(10);
			break;
		default:
			msleep(10);
		}
	}
}

void GWavelengthMeterWS6::PopulateDeviceWidget(GDeviceWidget* theDeviceWidget )
{
// 	// layout (in a groupbox) for the channels
// 	QFormLayout* ChannelsFormLayout = new QFormLayout();
// 	theDeviceWidget->AddSubGroupBox("Channels", ChannelsFormLayout);
// 	// a combo to drag and drop the subdevices in the lab
// 	QComboBox* pCombo = new QComboBox(theDeviceWidget);
// 	pCombo->view()->setDragDropMode(QAbstractItemView::DragOnly);
// 	pCombo->setModel(new GDeviceListModel(pCombo));
// 	// Let's populate the combo with names and the pointer to the corresponding GDevice's. (We use QVariant for that).
// 	foreach(GDevice* pDev, m_Channels) {
// 		pCombo->addItem(pDev->Name(), QVariant::fromValue(pDev->UniqueSystemID()));
// 	}
// 	ChannelsFormLayout->addRow(tr("Channels:"), pCombo);
}

void GWavelengthMeterWS6::TheHFApiFiredAWLChangedEvent(double newWL)
{
// 	m_LastMeasure = newWL;
// 	m_VoltageOutput = ControlLoop(m_LastMeasure, m_WavelengthSetpoint);
}

void GWavelengthMeterWS6::EnableWLMonitoring(bool doMonitor)
{
	if(doMonitor)
		start();
	else
		m_ThreadWaitForEvents = false;
}

void GWavelengthMeterWS6::EnableWLLocking(bool doLock)
{

}

void GWavelengthMeterWS6::CreateSubDevicesChannels()
{
	// get the number of channels in the WS6
	int numberChan = GetChannelsCount(0);
	for(int nCh = 1; nCh <= numberChan; nCh++) {
		GWS6Channel* pChan = new GWS6Channel(UniqueSystemID() + QString("-ch") + QString::number(nCh), this);
		m_Channels.append(pChan);
	}
}