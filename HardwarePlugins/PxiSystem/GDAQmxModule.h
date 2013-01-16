#ifndef GDAQmxModule_H
#define GDAQmxModule_H
#include "pxilabexe_global.h"

#include <QString>
#include "stdafx.h"
//class CNiDAQmxDevice;

/////////////////////////////////////////////////////////////////////
//! \brief The GDAQmxModule class should be (multiply) inherited by devices' class that represent a NiDAQmx object.
/*!
*/
class PXILABEXE_EXPORT GDAQmxModule
{
public:
	GDAQmxModule(QString NiDeviceName);
	~GDAQmxModule(void);

	//! Returns true if NiDAQmxDevice valid, e.g. does its name exists in the PXI chassis
	bool IsValid() const { return m_IsValidDevice; }
	//! Returns the number of the chassis in which the module is
	int ChassisNumber() const { return m_ChassisNumber; }
	//! Returns the number of the module in its chassis
	int SlotNumber() const { return m_SlotNumber; }

protected:
	//! Allows you to pre-create some (or all) the GDevice that represents each channel in the module.
	virtual void CreateSubDevicesChannels() = 0;
	//! Returns the Ni object that represents the device
	CNiDAQmxDevice NiDevice();

private:
	//! The chassis number of the module
	int m_ChassisNumber;
	//! The slot number of the module
	int m_SlotNumber;
	//! The name for this device in the DAQmx system
	QString m_NiDeviceName;
	//! Is this NiDAQmxDevice valid, e.g. does its name exists in the PXI chassis
	bool m_IsValidDevice;
};

#endif // GDAQmxModule_H
