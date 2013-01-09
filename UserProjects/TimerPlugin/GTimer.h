#ifndef GTimer_H
#define GTimer_H

#include "device.h"
#include "param.h"
/////////////////////////////////////////////////////////////////////
//! \brief The GTimer class implements a GProgDevice.
/*!
This soft device allows you to define an input parameter by drag-and-dropping it in a param-bucket. 
When the input is updated, the average over the past \e n values is calculated and displayed at the output. 
The value of \e n is defined by a spin-box.
If there are not yet \e n values in the past history of the parameter, the average is made on all existing data. 
The reset button clears the history of the parameter.
*/
//[inheritance]
class GTimer : public GProgDevice
//[inheritance]
{
	Q_OBJECT

public:

//[constructor]
	//! Constructor
	GTimer(QObject *parent, QString uniqueIdentifierName = "");
//[constructor]
	~GTimer();

public slots:

//![PopulateDeviceWidget]
protected:
	//! Re-implemented to provide a new widget adequately connected to this GTimer.
	void PopulateDeviceWidget(GDeviceWidget* theDeviceWidget);
//![PopulateDeviceWidget]

//! [variables]
private:
	GParamString	m_Delay;		//! Delay time (QDateTime format, "hh:mm;ss.zzz"). 
	GParamBool		m_SingleShot;	//! User wants a single trigger after a delay. 
	GParamInt		m_NumTriggers;	//! Number of triggers during timing sequence.
	GParamDouble	m_ElapsedTime;	//! Elapsed time (s), updated when timer triggers. Helpful because timer can miss triggers.
	GParamBucket	m_OutputBucket;	//! Output bucket to hold timer's outputs.

	QPushButton*	statusButton;	//! Start/Stop button for the user.  
	GParamBool		m_Status;		//! True if timer is running, false otherwise. 
	
	int				q_StartTime;	//! Saved time when timer began, for calculating m_ElapsedTime.
	QTimer			*m_Timer;		//! The timer itself. 	

private slots:
	//! User clicked the button to start/stop the timer:
	void UserChangeStatus();
	//! Called when timer is triggered
	void TimerTriggered();
};

#endif // GTimer_H
