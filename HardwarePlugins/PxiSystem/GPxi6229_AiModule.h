#ifndef GPXI6229_AIMODULE_H
#define GPXI6229_AIMODULE_H

#include "device.h"
#include "GDAQmxModule.h"

/////////////////////////////////////////////////////////////////////
//! \brief The GPxi6229_AiModule is a GDevice that represents the PXI-6229 Module in the PXI system.
/*!
It mainly contains a collection of analog input sub-devices that will appear in the device shelf.
*/
class GPxi6229_AiModule : public GHardDevice, public GDAQmxModule
{	
	// needs Q_OBJECT to use the inherits function
	Q_OBJECT

public:
	GPxi6229_AiModule(QString NiDeviceName, QObject *parent);
	~GPxi6229_AiModule();

	//! Reimplemented from GDevice
	QList<GDevice*> SubDevices() const;

protected:
	//! Reimplemented from GDAQmxModule
	void CreateSubDevicesChannels();
	//! Reimplemented from GDevice
	virtual void PopulateDeviceWidget(GDeviceWidget* theDeviceWidget);

private:
	QList<GDevice*> m_ListAI;
	
};

#endif // GPXI6229_AIMODULE_H
