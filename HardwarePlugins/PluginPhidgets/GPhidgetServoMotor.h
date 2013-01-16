#ifndef GPhidgetServoMotor_H
#define GPhidgetServoMotor_H
#include "pluginphidgets_global.h"

#include "device.h"
#include "param.h"
#include "Device/GServoMotor.h"
class GPhidgetAdvancedServoModule;

/////////////////////////////////////////////////////////////////////
//! \brief The GPhidgetServoMotor class implements the GServoMotor class for a servomotor controlled through the phidget API
/*!
The uniqueIdentifierName has to be on the form provided by GPhidgetAdvancedServoModule::CreateUniqueServoIdentifier(int indexServo).
*/
class PLUGINPHIDGETS_EXPORT GPhidgetServoMotor : public GServoMotor
{
	Q_OBJECT

public:
	GPhidgetServoMotor(QString uniqueIdentifierName, QObject *parent);
	~GPhidgetServoMotor();

	//! Reimplemented to add some stuff to check in order to qualify the device as "able".
	virtual bool IsAble() const;
	//! returns the parent Module if there is one.
	GPhidgetAdvancedServoModule* ParentModule() const;
	//! returns the index of this motor in the parent Module. -1 if problem.
	int IndexMotor() const;

	//! Provides extra settings in a new widget
	QWidget* ProvideNewExtraSettingsWidget(QWidget* parentWidget);

public slots:
	//! Re-implemented.
	virtual void MoveAbsolute(double newPos);
	//! Re-implemented.
	virtual void SetMaxVelocity(double maxVel);
	//! Re-implemented.
	virtual void SetMaxAcceleration(double maxAcc);

protected slots:
	//! Re-implemented.
	void Engage( bool doEngage );
	//! Re-implemented.
	void Disengage();

protected:
	//! Reimplemented from GDevice
	virtual void PopulateDeviceWidget(GDeviceWidget* theDeviceWidget);
	//! Reimplemented from GDevice. Provides a shorter name for the servo.
	virtual QString DefaultShortName() const;
// 	//! Reimplemented 
// 	void DelayedInterpretSettings( QSettings& fromQsettings );

signals:
	// Emitted when the servo object is informed that it has moved.
	void PositionChanged( double thePos, double theVel );

private:
	//! Called by the module when it detected a position change
	void ModuleTriggeredPositionChanged( double thePos, double theVel );
	double m_VelocityWhenLastChecked;
	//! The max velocity 
	GParamDouble m_VelocityLimit;
	//! The max acceleration 
	GParamDouble m_AccelerationLimit;


	friend class GPhidgetAdvancedServoModule;
	friend class GPhidgetServoMotorWidget;
};

#endif // GPhidgetServoMotor_H
