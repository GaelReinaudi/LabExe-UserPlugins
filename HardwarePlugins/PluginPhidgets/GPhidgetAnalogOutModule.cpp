#include "GPhidgetAnalogOutModule.h"
#include "GPhidgetManager.h"
#include "GPhidgetOutput.h"

#include "GPhidget21.h"

G_REGISTER_HARD_DEVICE_CLASS(GPhidgetAnalogOutModule)

GPhidgetAnalogOutModule::GPhidgetAnalogOutModule(QString uniqueIdentifierName, QObject *parent)
	: GPhidgetModule(uniqueIdentifierName, parent)
	, m_TheCPhidgetAnalog(0)
	, m_NumberOutput(0)
{
	m_SerialNumber = GPhidgetManager::GetSerialFromPhidgetIdentifier(UniqueSystemID());
	if(!m_SerialNumber)
		return;
	//create the advanced servo object
	CPhidgetAnalog_create(&m_TheCPhidgetAnalog);
}

GPhidgetAnalogOutModule::~GPhidgetAnalogOutModule()
{
	if(!m_TheCPhidgetAnalog)
		return;
	//... terminate the program so we will close the phidget and delete the object we created
	CPhidget_close(TheCPhidgetHandle());
	CPhidget_delete(TheCPhidgetHandle());
	//all done, exit
}

bool GPhidgetAnalogOutModule::IsAble() const
{
	if(GPhidgetModule::IsAble())
		if(m_TheCPhidgetAnalog)
			return true;
	return false;
}

void GPhidgetAnalogOutModule::DelayedPhidgetInitialization()
{
	ConfigureWhenPluggedIn();
}

void GPhidgetAnalogOutModule::ConfigureWhenPluggedIn()
{
	// get the number of sensors
	CPhidgetAnalog_getOutputCount(m_TheCPhidgetAnalog, &m_NumberOutput);
	CreateSubDevicesOutputs();

	for(int indexOutput = 0; indexOutput < m_NumberOutput; indexOutput++) {
		CPhidgetAnalog_setEnabled(m_TheCPhidgetAnalog, indexOutput, true);
		GPhidgetOutput* pOut = Output(indexOutput);
		if(pOut) {
			pOut->SetOutputValue(pOut->OutputValue());
		}
	}
	emit IsAblenessMayHaveChanged(IsAble());
}

void GPhidgetAnalogOutModule::PopulateDeviceWidget(GDeviceWidget* theDeviceWidget )
{
// 	QLayout* outputsLayout = theDeviceWidget->layout();
// 	if(!outputsLayout)
// 		outputsLayout = new QVBoxLayout(theDeviceWidget);
// 	// a combo to drag and drop the subdevices in the lab
// 	QComboBox* pComboOutputs = new QComboBox(theDeviceWidget);
// 	pComboOutputs->view()->setDragDropMode(QAbstractItemView::DragOnly);
// 	pComboOutputs->setModel(new GDeviceListModel(pComboOutputs));
// 	// Let's populate the combo with names and the pointer to the corresponding GDevice's. (We use QVariant for that).
// 	foreach(GDevice* pDev, m_Outputs) {
// 		pComboOutputs->addItem(pDev->Name(), QVariant::fromValue(pDev->UniqueSystemID()));
// 	}
// 	outputsLayout->addWidget(pComboOutputs);
}

void GPhidgetAnalogOutModule::CreateSubDevicesOutputs()
{
	if(!IsAble())
		return;
	m_Outputs.clear();
	for(int indexOutput = 0; indexOutput < m_NumberOutput; indexOutput++) {
		QString nameOutput = CreateUniqueOutputIdentifier(indexOutput);
		// if it already exist, lets not make it again.
		GDevice* pOutput = GetDeviceFromDeviceManager(nameOutput);
		// but let's make sure or set the correct parent module (in case it was created	at startup, without the module parent created...)
		if(pOutput)// && pOutput->parent() != this)
			pOutput->setParent(this);
		else
			pOutput = new GPhidgetOutput(nameOutput, this);
		m_Outputs.append(pOutput);
		disconnect(this, SIGNAL(IsAblenessMayHaveChanged(bool)), pOutput, SIGNAL(IsAblenessMayHaveChanged(bool)));
		connect(this, SIGNAL(IsAblenessMayHaveChanged(bool)), pOutput, SIGNAL(IsAblenessMayHaveChanged(bool)), Qt::QueuedConnection);
	}
}

QString GPhidgetAnalogOutModule::CreateUniqueOutputIdentifier( int indexOutput ) const {
	return UniqueSystemID() + QString("%1%2").arg(PHIDGET_ANALOG_OUTPUT_NUMBER_SEPARATOR).arg(indexOutput);
}

int GPhidgetAnalogOutModule::GetIndexOutputFromPhidgetOutputIdentifier( QString strUniqueID )
{
	bool conversionOK = false;
	int indexOutput = strUniqueID.split(PHIDGET_ANALOG_OUTPUT_NUMBER_SEPARATOR).last().toInt(&conversionOK);
	if(conversionOK)
		return indexOutput;
	else
		return -1;
}

GPhidgetOutput* GPhidgetAnalogOutModule::Output( int indexOutput ) const
{
	if(indexOutput < SubDevices().count())
		return qobject_cast<GPhidgetOutput*>(SubDevices().at(indexOutput));
	return 0;
}

void GPhidgetAnalogOutModule::SetNewOutputValue( int indexOutput, double newValue )
{
	CPhidgetAnalog_setVoltage(m_TheCPhidgetAnalog, indexOutput, newValue);
}