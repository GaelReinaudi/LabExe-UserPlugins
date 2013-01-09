#ifndef GParamSupplier_H
#define GParamSupplier_H

#include "device.h"
#include "param.h"
/////////////////////////////////////////////////////////////////////
//! \brief The GParamSupplier class implements a GProgDevice.
/*!
This soft device allows you to define an input parameter by drag-and-dropping it in a param-bucket. 
When the input is updated, the average over the past \e n values is calculated and displayed at the output. 
The value of \e n is defined by a spin-box.
If there are not yet \e n values in the past history of the parameter, the average is made on all existing data. 
The reset button clears the history of the parameter.
*/
//[inheritance]
class GParamSupplier : public GProgDevice
//[inheritance]
{
	Q_OBJECT

public:

//[constructor]
	//! Constructor
	GParamSupplier(QObject *parent, QString uniqueIdentifierName = "");
//[constructor]
	~GParamSupplier();

public slots:
	//! Makes the filter to compute the output based on the History of the parameter being filtered
	void UpdateOutput();

//![PopulateDeviceWidget]
protected:
	//! Re-implemented to provide a new widget adequately connected to this GParamSupplier.
	void PopulateDeviceWidget(GDeviceWidget* theDeviceWidget);
//![PopulateDeviceWidget]

//! [variables]
private:
//! [m_InputBucket]
	//! the bucket for the input parameter
	GSingleParamBucket m_InputBucket;
//! [m_InputBucket]
//! [m_SuppliedBucket]
	//! the output bucket that holds the param being supplied
	GParamBucket m_SuppliedBucket;
//! [m_SuppliedBucket]
//! [m_ActiveParamIndex]
	//! the number representing the param being selected for being supplied.
	GSingleParamBucket m_ActiveParamIndex;
//! [m_ActiveParamIndex]
//! [m_AbsoluteSupply]
	//! tells to transfer the whole input value to the selected params
	GParamBool m_AbsoluteSupply;
//! [m_AbsoluteSupply]
	//! telling to wrap around the selection index so that it cycles through the params.
	GParamBool m_DoWrap;
	//! if ON, Makes the selection process be the one of a mask whose bit represent each param. ex: 5 = 0000101 = param 0 and 2 selected
	GParamBool m_DoBinary;
	//! keeps track of the relative changes when not in absolute transfer
	double m_lastInUpdate;
	//! [variables]

private slots:
	//! Called when a sample arrives and computes the new output.
	void EventSampleArrived(double newValue);
	//! Called when the selection param changed.
	void ChangeSelection();
};

#endif // GParamSupplier_H
