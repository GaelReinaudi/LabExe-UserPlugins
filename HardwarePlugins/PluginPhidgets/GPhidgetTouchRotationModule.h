#ifndef GPHIDGETTOUCHROTATIONMODULE_H
#define GPHIDGETTOUCHROTATIONMODULE_H

#include "GPhidgetInterfaceKitModule.h"
#include "GPhidgetModule.h"
#include "param.h"

class GPhidgetTouchRotationModule : public GPhidgetInterfaceKitModule
{
	Q_OBJECT

public:
	GPhidgetTouchRotationModule(QString uniqueIdentifierName, QObject *parent);
	~GPhidgetTouchRotationModule();

protected:
	//! Called by the OnSensorChange_Handler.
	void TriggeredSensorValueChanged(int indexSensor, int theValue);
	//! Called by the OnInputChange_Handler.
	void TriggeredDigitalInputValueChanged(int indexDigIn, bool theValue);
	//! Reimplemented
	virtual void PopulateDeviceWidget(GDeviceWidget* theDeviceWidget);

private:
	int m_lastValue;
	GParamBool m_Proximity;
	GParamBool m_Touching;
	GParamInt m_CumulativeTicks;
	GParamInt m_TouchTicks;
	GParamInt m_TouchCount;

};

#endif // GPHIDGETTOUCHROTATIONMODULE_H
