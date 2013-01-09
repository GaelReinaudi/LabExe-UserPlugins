#ifndef GSRSController_H
#define GSRSController_H

#include "device.h"
#include "param.h"

/////////////////////////////////////////////////////////////////////
//! \brief The GSRSController class implements a GProgDevice.
/*!
This soft device allows you to define an input parameter by drag-and-dropping it in a param-bucket. 
When the input is updated, the average over the past \e n values is calculated and displayed at the output. 
The value of \e n is defined by a spin-box.
If there are not yet \e n values in the past history of the parameter, the average is made on all existing data. 
The reset button clears the history of the parameter.
*/
//[inheritance]
class GSRSController : public GProgDevice
//[inheritance]
{
	Q_OBJECT

public:

//[constructor]
	//! Constructor
	GSRSController(QObject *parent, QString uniqueIdentifierName = "");
//[constructor]
	~GSRSController();

//![PopulateDeviceWidget]
protected:
	//! Re-implemented to provide a new widget adequately connected to this GSRSController.
	void PopulateDeviceWidget(GDeviceWidget* theDeviceWidget);
//![PopulateDeviceWidget]

//! [variables]
private:
	int m_SgIsConnected;
	
	/*QAbstractButton findButton;
	QAbstractButton moreButton;
	QDialogButtonBox buttonBox;
	*/
	//GParamDouble m_CurrentFreq;
	GParamDouble m_ModulationDev;
	GParamDouble m_ModulationRate;
	GParamDouble m_Frequency;
	GParamDouble m_ShiftTime;
	GParamDouble m_BabyStepSize;

	GParamBool m_SweepStatus;
	GParamBool m_IsConnected;

	GParamString m_IPAddress;
	
	//GParamBool m_ReadFreq;

	//QLineEdit *IPLineEdit;// = new QLineEdit();

	double m_FreqDouble;
	double m_PrevFreq;
	QList<double> m_History;
//! [variables]

private slots:
	void SetFrequencyStart(double freq);
	void SetFrequencyStop();
	void SetModulationDev(double modDev);
	void SetModulationRate(double modRate);
	void SetSweepStatus(bool sweeponoff);
	void SetIPAddress(QString ip);
};

#endif // GSRSController_H
