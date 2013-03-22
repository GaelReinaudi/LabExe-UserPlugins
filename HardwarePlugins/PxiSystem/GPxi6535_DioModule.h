#ifndef GPXI6535_DIOMODULE_H
#define GPXI6535_DIOMODULE_H
#include "pxilabexe_global.h"

#include "device.h"
#include "GDAQmxModule.h"

/////////////////////////////////////////////////////////////////////
//! \brief The GPxi6535_DioModule is a GDevice that represents the PXI-6535 Module in the PXI system.
/*!
It mainly contains a collection of digital input/output sub-devices that will appear in the device shelf.
*/
class PXILABEXE_EXPORT GPxi6535_DioModule : public GHardDevice, public GDAQmxModule
{
	Q_OBJECT

public:
	GPxi6535_DioModule(QString NiDeviceName, QObject *parent);
	~GPxi6535_DioModule();

	//! Reimplemented from GDevice
	QList<GDevice*> SubDevices() const;

protected:
	//! Reimplemented from GDAQmxModule
	void CreateSubDevicesChannels();
	//! Reimplemented from GDevice
	virtual void PopulateDeviceWidget(GDeviceWidget* theDeviceWidget);

private:
	QList<GDevice*> m_ListDO;

};

#endif // GPXI6535_DIOMODULE_H
