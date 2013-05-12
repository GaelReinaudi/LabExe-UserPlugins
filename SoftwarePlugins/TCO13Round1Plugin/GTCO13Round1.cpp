#include "GTCO13Round1.h"

GTCO13Round1::GTCO13Round1(QObject *parent, QString uniqueIdentifierName /* = "" */)
	: GProgDevice(parent, uniqueIdentifierName)
	, m_ExamplesString("running examples", this)
	, m_CmdString("cmd line", this, GParam::ReadOnly)
	, m_ArgBucket("arguments", this)
	, m_Output("average cost", this, GParam::ReadOnly)
	, m_NumExLeft("ex left", this, GParam::ReadOnly)
	, m_TotalNumExToCompareForNumberOfExamplesRefScored(0)
{
	m_Output.SetHardLimits(-1, 9e12);
	// Default value of the sample size for the first use.
	// It will be over-written if a previously saved value is read from a file.
	m_ExamplesString = "1 2 3 4 5 6 7 8 9 10";
	// Connects the input bucket to the event that starts a calculation of the average
	connect(&m_ArgBucket, SIGNAL(BucketUpdatedValues(int)), this, SLOT(EventSampleArrived(int)));
	// make a evaluation of the examples that the latter results will be compared against;
	connect(&m_ExamplesString, SIGNAL(ValueUpdated(QString)), this, SLOT(EventExampleChanged(QString)));

	for(int i = 0; i < 30 ; i++) {
		par[i] = new GParamDouble(QString("par%1").arg(i), this);
		m_ArgBucket.AddParam(par[i]);
	}
}

GTCO13Round1::~GTCO13Round1()
{

}

void GTCO13Round1::PopulateDeviceWidget(GDeviceWidget* theDeviceWidget )
{
	// We add a vertical layout to hold together all the widgets that we are going to display.
	QVBoxLayout* pVlay = new QVBoxLayout();
	theDeviceWidget->AddSubLayout(pVlay);

	pVlay->addWidget(m_ExamplesString.ProvideNewLabel(theDeviceWidget));
	pVlay->addWidget(m_ExamplesString.ProvideNewParamLineEdit(theDeviceWidget));
	pVlay->addWidget(m_CmdString.ProvideNewLabel(theDeviceWidget));
	pVlay->addWidget(m_CmdString.ProvideNewParamLineEdit(theDeviceWidget));

	pVlay->addWidget(m_ArgBucket.ProvideNewParamWidget(theDeviceWidget));
	// We add a form layout that will hold the numerical settings.
 	QFormLayout* pFLay = new QFormLayout();
	pVlay->addLayout(pFLay);
	pFLay->addRow(m_NumExLeft.ProvideNewLabel(theDeviceWidget), m_NumExLeft.ProvideNewParamSpinBox(theDeviceWidget));
	pFLay->addRow(m_Output.ProvideNewLabel(theDeviceWidget), m_Output.ProvideNewParamSpinBox(theDeviceWidget));
	// We add an expandable space.
	pVlay->addStretch();
}

void GTCO13Round1::EventSampleArrived(int numParUp)
{
	QString program = "java";
	program += " -jar \"F:/NewFolder/TCO13/TCO13SnowCleaning/SnowCleaningVis.jar\"";
	program += " -exec \"F:/NewFolder/TCO13/TCO13SnowCleaning/Release/TCO13SnowCleaning.exe %1\"";
	program += " -seed %2";
	program += " -novis";

	QString exs = m_ExamplesString.StringValue();
	QVector<int> ExsInd;
	m_ExsProcess.clear();
 	m_NumEx = 0;
	m_Score = 0.0;
	// make the vector of ex indexes
	foreach(const QString & ex, exs.split(" ", QString::SkipEmptyParts)) {
		ExsInd.append(ex.toInt());
		m_NumEx++;
	}
	m_NumExLeft = m_NumEx;

	QString argstring;
	foreach(const double & val, m_ArgBucket.DoubleValues()) {
		argstring += QString(" %1").arg(val, 2, 'f', 4);
	}

	// if we have no values to compare the latter results to, we need to calculate them first by using the program with no arguments
	if(m_ScoresCompareEx.isEmpty()) {
		program = program.arg("");
		m_TotalNumExToCompareForNumberOfExamplesRefScored = m_NumEx;
	}
	else {
		program = program.arg(argstring);
	}

	m_CmdString = program;

	foreach(int exInd, ExsInd) {
		QProcess *myProcess = new QProcess(this);
		m_ExsProcess.insert(exInd, myProcess);
		// connect
		connect(myProcess, SIGNAL(readyReadStandardOutput()), this, SLOT(EventResultTestOutput()));
		myProcess->start(program.arg(exInd));
	}
}

void GTCO13Round1::EventResultTestOutput()
{
	QProcess* pro = qobject_cast<QProcess*>(sender());
	if(!pro)
		return;

	QString outstr(pro->readAllStandardOutput());
	int scoreInd = outstr.indexOf("Score");
	int indexEx = m_ExsProcess.key(pro);
	if(scoreInd != -1) {
		double tempsc = outstr.mid(scoreInd + 8).toDouble();
		if(tempsc < 0.0)
			tempsc = 1e10;
		// if no score to compare with, we take this one as the reference to compare the latter scores with
		if(m_ScoresCompareEx.size() < m_TotalNumExToCompareForNumberOfExamplesRefScored) {
			m_ScoresCompareEx.insert(indexEx, tempsc);
		}
		// else we simply compute the ratio. For the first time it should make an average of 1.
		m_Score += 1e6 * m_ScoresCompareEx.value(indexEx) / tempsc;
		m_NumEx--;
	}
	m_NumExLeft = m_NumEx;
	// if we have all results
	if(m_NumEx <= 0) {
		m_Score /= double(m_ScoresCompareEx.size());
		UpdateOutput();
	}
	// delete the process to free memory
// 	pro->kill();
// 	pro->deleteLater();
}

void GTCO13Round1::UpdateOutput()
{
	m_Output = m_Score;
}

void GTCO13Round1::EventExampleChanged( QString newExStr )
{
	m_ScoresCompareEx.clear();
}



















