#include "GDAQmxModule.h"

GDAQmxModule::GDAQmxModule(QString NiDeviceName)
{
	m_ChassisNumber = 0;
	m_SlotNumber = 0;
	m_NiDeviceName = NiDeviceName;
	try
	{
		CNiDAQmxSystem::LoadDevice(m_NiDeviceName.toAscii());
		m_IsValidDevice = true;
	}
	catch (CNiDAQmxException *exception)
	{
		exception->ReportError();
		exception->Delete();
		m_IsValidDevice = false;
	}
	if(!IsValid())
		return;
	m_ChassisNumber = NiDevice().PxiChassisNumber;
	m_SlotNumber = NiDevice().PxiSlotNumber;
}

GDAQmxModule::~GDAQmxModule(void)
{
}

CNiDAQmxDevice GDAQmxModule::NiDevice()
{
	try
	{
		return CNiDAQmxSystem::LoadDevice(m_NiDeviceName.toAscii());
	}
	catch (CNiDAQmxException *exception)
	{
		exception->ReportError();
		exception->Delete();
		m_IsValidDevice = false;
	}
}
