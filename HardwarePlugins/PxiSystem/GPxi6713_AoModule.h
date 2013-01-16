#ifndef GPXI6713_AOMODULE_H
#define GPXI6713_AOMODULE_H
#include "pxilabexe_global.h"

#include "device.h"
#include "GDAQmxModule.h"

/////////////////////////////////////////////////////////////////////
//! \brief The GPxi6713_AoModule is a GDevice that represents the PXI-6713 Module in the PXI system.
/*!
It mainly contains a collection of analog output sub-devices that will appear in the device shelf.
*/
class PXILABEXE_EXPORT GPxi6713_AoModule : public GHardDevice, public GDAQmxModule
{
	// needs Q_OBJECT to use the inherits function
	Q_OBJECT

public:
	GPxi6713_AoModule(QString NiDeviceName, QObject *parent);
	~GPxi6713_AoModule();

	//! Reimplemented from GDevice
	QList<GDevice*> SubDevices() const {return m_ListAO;}

protected:
	//! Reimplemented from GDAQmxModule
	void CreateSubDevicesChannels();
	//! Reimplemented from GDevice
	virtual void PopulateDeviceWidget(GDeviceWidget* theDeviceWidget);

private:
	QList<GDevice*> m_ListAO;
	
};

#endif // GPXI6713_AOMODULE_H
