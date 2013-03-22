#ifndef GPXISYSTEM_H
#define GPXISYSTEM_H
#include "pxilabexe_global.h"

#include "device.h"

/////////////////////////////////////////////////////////////////////
//! \brief The GPxiSystem is a GDevice that represents the Ni PXI system.
/*!
It mainly contains the CreateSubDevicesModules() function that queries the modules 
in the system and create the appropriate GDevice object (like GPxi6713_AoModule).
*/
class PXILABEXE_EXPORT GPxiSystem : public GHardDevice
{
public:
	GPxiSystem(QString uniqueIdentifierName, QObject* parent);
	~GPxiSystem();

	void Initialize() {}
	int PxiSlotNumber(QString NiDeviceName) const;
	QList<GDevice*> SubDevices() const {return m_PxiSlot_GDeviceModule.values();}

protected:
	virtual void PopulateDeviceWidget(GDeviceWidget* theDeviceWidget);

private:
	//! Creates the GDevice objects that correspond to each detected module in the slots of the PXI.
	void CreateSubDevicesModules();

private:
	//! The QMap that associated a slot number to the actual GDevice* of the module.
	//! This has to be populated so that each module is in the QList returned by SubDevices()
	QMap<int, GDevice*> m_PxiSlot_GDeviceModule;
};

#endif // GPXISYSTEM_H
