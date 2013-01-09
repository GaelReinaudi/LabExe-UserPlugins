#ifndef GLockingSlapper_H
#define GLockingSlapper_H

#include "device.h"
#include "param.h"

/////////////////////////////////////////////////////////////////////
//! \brief The GLockingSlapper class implements a GProgDevice.
/*!
This soft device allows you to define an input parameter by drag-and-dropping it in a param-bucket. 
When the input is updated, the average over the past \e n values is calculated and displayed at the output. 
The value of \e n is defined by a spin-box.
If there are not yet \e n values in the past history of the parameter, the average is made on all existing data. 
The reset button clears the history of the parameter.
*/
class GLockingSlapper : public GProgDevice
{
	Q_OBJECT

public:

	//! Constructor
	GLockingSlapper(QObject *parent, QString uniqueIdentifierName = "");
	~GLockingSlapper();

public slots:
	//! Makes the locker to compute the output based on the error signal and the gain
	void Iteration();

protected:
	//! Re-implemented to provide a new widget adequately connected to this GLockingSlapper.
	void PopulateDeviceWidget(GDeviceWidget* theDeviceWidget);

private:
	//! the bucket for the input parameter
	GSingleParamBucket m_SetPointBucket;
	GSingleParamBucket m_InputBucket;
	GSingleParamBucket m_OutputBucket;
	GParamDouble m_Gain;
	GParamDouble m_MaxSlapSize;
	GParamDouble m_ErrorSignal;
	GParamBool m_Enable;
};

#endif // GLockingSlapper_H
