#ifndef GTCO13Round1_H
#define GTCO13Round1_H

#include "device.h"
#include "param.h"
/////////////////////////////////////////////////////////////////////
//! \brief The GTCO13Round1 class implements a GProgDevice.
/*!
This soft device ...
*/
class GTCO13Round1 : public GProgDevice
{
	Q_OBJECT

public:
	GTCO13Round1(QObject *parent, QString uniqueIdentifierName = "");
	~GTCO13Round1();

public slots:
	//! Makes the filter to compute the output based on the History of the parameter being filtered
	void UpdateOutput();

protected:
	//! Re-implemented to provide a new widget adequately connected to this GTCO13Round1.
	void PopulateDeviceWidget(GDeviceWidget* theDeviceWidget);

private slots:
	//! Called when a sample arrives and computes the new output.
	void EventSampleArrived(int numParUp);
	//! called when a test is finished
	void EventResultTestOutput();
	void EventExampleChanged( QString newExStr );

private:
	//! the bucket for the arguments values
	GParamBucket m_ArgBucket;
	//! the output of the test
	GParamDouble m_Output;
	//! the examples to test on
	GParamString m_ExamplesString;
	//! command line that will be passed to the process
	GParamString m_CmdString;

	GParamDouble* par[30];
	QHash<int, QProcess*> m_ExsProcess;
	QHash<int, double> m_ScoresCompareEx;
	int m_NumEx;
	int m_TotalNumExToCompareForNumberOfExamplesRefScored;
	double m_Score;
	GParamInt m_NumExLeft;
};

#endif // GTCO13Round1_H
