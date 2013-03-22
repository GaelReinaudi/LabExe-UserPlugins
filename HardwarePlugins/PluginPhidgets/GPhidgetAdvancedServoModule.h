#ifndef GPHIDGETADVANCEDSERVOMODULE_H
#define GPHIDGETADVANCEDSERVOMODULE_H
#include "pluginphidgets_global.h"

#include "GPhidgetModule.h"
class GPhidgetServoMotor;

typedef struct _CPhidgetAdvancedServo *CPhidgetAdvancedServoHandle;

#define PHIDGET_SERVO_NUMBER_SEPARATOR (QString("S"))

/////////////////////////////////////////////////////////////////////
//! \brief The GPhidgetAdvancedServoModule class encapsulate a Phidget servo module.
/*!
It handles some phidget servo modules event events like:
- GServoModulePositionChangeHandler() is function called when a phidget servo module considers a servo moved. The phidget API 
knows that it has to call this function because I call this Phidget-API function:
\code CPhidgetAdvancedServo_set_OnPositionChange_Handler(m_TheCPhidgetAdvancedServo, GServoModulePositionChangeHandler, this); \endcode

It defines the list of GPhidgetServoMotor sub devices defined in the derived class. 
It will be used for display on a GDeviceShelf.
The GPhidgetAdvancedServoModule takes care of creating the GPhidgetServoMotor objects that will represents the servomotors in the program.
*/
class PLUGINPHIDGETS_EXPORT GPhidgetAdvancedServoModule : public GPhidgetModule
{
	Q_OBJECT

public:
	GPhidgetAdvancedServoModule(QString uniqueIdentifierName, QObject *parent);

	~GPhidgetAdvancedServoModule();

	//! Reimplemented from GDevice to add some stuff to check in order to qualify the device as "able".
	bool IsAble() const;

	//! Reimplemented from GDevice
	QList<GDevice*> SubDevices() const {return m_ListServos;}
	//! Returns the GPhidgetServoMotor* from the indexServo. 0 if not.
	GPhidgetServoMotor* Servo(int indexServo) const;
	//! A function to get the index of a given servo motor from its strUniqueID
	static int GetIndexServoFromPhidgetServoIdentifier(QString strUniqueID);

	//! Gets the target position of the servo with indexServo
	double GetTargetPosition(int indexServo) const;
	//! Sets the target position of the servo with indexServo to the newAngle
	void SetTargetPosition(int indexServo, double newAngle);
	//! engage or disengage the servo with indexServo
	void SetEngage(int indexServo, bool doEngage);
	//! Tells if the servo with indexServo is stopped (see the phidget programing API).
	bool IsStopped(int indexServo);
	//! Sets the max velocity for the phidget control of this servo
	void SetVelocityLimit(int indexServo, double newVelMax);
	//! Sets the max acceleration for the phidget control of this servo
	void SetAccelerationLimit(int indexServo, double newAccMax);

protected:
	//! Reimplemented
	CPhidgetHandle TheCPhidgetHandle() const { return (CPhidgetHandle)m_TheCPhidgetAdvancedServo; }
	//! reimplemented
	void ConfigureWhenPluggedIn();
	//! reimplemented
	virtual void DelayedPhidgetInitialization();
	//! Creates the servos GDevice's
	void CreateSubDevicesServos();
	//! Reimplemented
	virtual void PopulateDeviceWidget(GDeviceWidget* theDeviceWidget);
	//! Called by the OnVelocityChange_Handler. IT DOESN'T GET TRIGGERED FOR SMALL TRAVELS (the handler doesn't react somehow)
	void TriggeredVelocityChanged(int indexServo, double theVel);
	//! Called by the OnPositionChange_Handler.
	void TriggeredPositionChanged(int indexServo, double thePos, double theVelo);

private:
	//! A function to create the name of the servo.
	QString CreateUniqueServoIdentifier(int indexServo) const;

private:
	CPhidgetAdvancedServoHandle m_TheCPhidgetAdvancedServo;
	int m_NumberMotors;
	QList<GDevice*> m_ListServos;
	
	friend int __stdcall GServoModulePositionChangeHandler(CPhidgetAdvancedServoHandle ADVSERVO, void *pPhiMod, int Index, double Value);
	friend int __stdcall GServoModuleVelocityChangeHandler(CPhidgetAdvancedServoHandle ADVSERVO, void *pPhiMod, int Index, double Value);
};

#endif // GPHIDGETADVANCEDSERVOMODULE_H
