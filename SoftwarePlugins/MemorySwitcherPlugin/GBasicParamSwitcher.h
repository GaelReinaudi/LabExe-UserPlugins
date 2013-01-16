#ifndef GBASICPARAMSWITCHER_H
#define GBASICPARAMSWITCHER_H

#include "device.h"
#include "param.h"

/////////////////////////////////////////////////////////////////////
//! \brief The GBasicParamSwitcher class implements an switchable two-state memory for a param.
/*!
*/
class GBasicParamSwitcher : public GProgDevice
{
	Q_OBJECT

public:
	GBasicParamSwitcher(QObject *parent, QString uniqueIdentifierName = "");
	~GBasicParamSwitcher();

protected:
	//! Re-implemented
	virtual void PopulateDeviceWidget(GDeviceWidget* theDeviceWidget);

protected slots:
	//! Slot that assigns the first value if the trigger is even or the second if the trigger is odd
	void Switch();

private:
	//! the param bucket for the param to switch
	GSingleParamBucket m_BucketParam;
	//! the param bucket for the triggering event
	GSingleParamBucket m_BucketTrigger;
	//! First value of the switch
	GParamDouble m_FirstValue;
	//! Second value of the switch
	GParamDouble m_SecValue;
};

#endif // GBASICPARAMSWITCHER_H
