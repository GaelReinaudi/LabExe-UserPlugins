#include "GPxiSystem.h"
#include <QtGui>

#include "GPxi6713_AoModule.h"
#include "GPxi6229_AiModule.h"
#include "GPxi6535_DioModule.h"

#include "stdafx.h"

GPxiSystem::GPxiSystem(QString uniqueIdentifierName, QObject *parent)
	: GHardDevice(uniqueIdentifierName, parent)
{
	CreateSubDevicesModules();
}

GPxiSystem::~GPxiSystem()
{

}

void GPxiSystem::CreateSubDevicesModules()
{
	QStringList strDevices = NiToQString(CNiDAQmxSystem::GetDevices());
	foreach(QString NiDeviceNames, strDevices) {
		QString CardType = PxiDaqDevice(NiDeviceNames).ProductType;
		// The unique name for the device here has to be the Ni Device identifier because we will use it to control the card.
		QString uniqueIdentifierNameForDevice = NiDeviceNames;

		if(CardType == "PXI-6713") {
			m_PxiSlot_GDeviceModule.insert(PxiSlotNumber(NiDeviceNames), new GPxi6713_AoModule(uniqueIdentifierNameForDevice, this));
		}
		else if(CardType == "PXI-6229") {
			m_PxiSlot_GDeviceModule.insert(PxiSlotNumber(NiDeviceNames), new GPxi6229_AiModule(uniqueIdentifierNameForDevice, this));
		}
		else if(CardType == "PXI-6535" || CardType == "PXIe-6535") {
			m_PxiSlot_GDeviceModule.insert(PxiSlotNumber(NiDeviceNames), new GPxi6535_DioModule(uniqueIdentifierNameForDevice, this));
		}
	}
}

void GPxiSystem::PopulateDeviceWidget(GDeviceWidget* theDeviceWidget )
{
	foreach(GDevice* pdev, m_PxiSlot_GDeviceModule.values()) {
		GDeviceWidget* subDevWidget = pdev->ProvideNewDeviceGroupBox(theDeviceWidget);
		theDeviceWidget->layout()->addWidget(subDevWidget);
	}
}

int GPxiSystem::PxiSlotNumber( QString NiDeviceName ) const
{
	CNiDAQmxDevice theDev = PxiDaqDevice(NiDeviceName);
	int slotNumber = theDev.PxiSlotNumber;
	return slotNumber;
}
