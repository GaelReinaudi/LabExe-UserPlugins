#include "GPlainTextLogger.h"
#include "GPlainTextLoggerWidget.h"

#include "Script/GMathScriptEngine.h"

#include <QVBoxLayout>

GPlainTextLogger::GPlainTextLogger(QObject *parent, QString uniqueIdentifierName /* = "" */)
	: GProgDevice(parent, uniqueIdentifierName)
    , m_Bucket("Data", this)
    , m_BucketColNames("Col Names", this)
    , m_ShouldLogOnUpdate("On update?", this)
	, m_ShouldLogOnTimer("On timer?", this)
	, m_SecondTimer("Delay [s]:", this)
    , m_FolderPath("Folder", this/*, GParam::ReadOnly*/)
    , m_FileName("File name", this)
    , m_FirstColName("Col. name:", this)
    , m_FirstColFormula("Formula (use i,t,tu,tm):", this)
    , m_FirstColValue("=", this, GParam::ReadOnly)
	, m_UpdateCount(0)
	, m_SecUpdate("Elapsed time (s):", this, GParam::ReadOnly)
	, m_SecMidnight("sec mid", this, GParam::ReadOnly)
	, m_SecEpoch("sec epoch", this, GParam::ReadOnly)
	, m_CurrentIndexUpdate("Update #:", this, GParam::ReadOnly)
    , m_pNotePadProcess(nullptr)
{
	connect(&m_Bucket, SIGNAL(BucketUpdatedValues()), this, SLOT(EventBucketUpdated()));
	connect(&m_Timer, SIGNAL(timeout()), this, SLOT(EventTimerFired()));
	connect(&m_SecondTimer, SIGNAL(ValueUpdated(double)), this, SLOT(SetTimerLapse(double)));
	connect(&m_FileName, SIGNAL(ValueUpdated(QString)), this, SLOT(ResetCount()));
	connect(&m_FolderPath, SIGNAL(ValueUpdated(QString)), this, SLOT(ChooseFolder(QString)), Qt::QueuedConnection);

	m_SecUpdate.SetHardLimits(0.0, 9e99);
	m_SecMidnight.SetHardLimits(0.0, 9e99);
	m_SecEpoch.SetHardLimits(0.0, 9e99);
	m_FirstColValue.SetHardLimits(0.0, 9e99);

	m_SecondTimer = 1.0;
	m_SecondTimer.SetDisplayDecimals(2);
	m_SecondTimer.SetTypicalStep(0.1);
	m_SecondTimer.SetHardLimits(0.01, 9999);
	m_FirstColName = "unix time (s)";
	m_FirstColFormula = "t";

	m_Timer.start();
}

GPlainTextLogger::~GPlainTextLogger()
{

}

void GPlainTextLogger::PopulateDeviceWidget(GDeviceWidget* theDeviceWidget )
{
	GPlainTextLoggerWidget* pWidLog = new GPlainTextLoggerWidget(this, theDeviceWidget);

	QVBoxLayout* lay = new QVBoxLayout();
	theDeviceWidget->AddSubLayout(lay);
	lay->addWidget(pWidLog);
}

void GPlainTextLogger::ChooseFolder(QString folderPath /*= ""*/)
{
	if(folderPath.isEmpty()) {
        QFileDialog* pDialog = new QFileDialog(nullptr, "Select folder", m_FolderPath);
		pDialog->setFileMode(QFileDialog::Directory);
		pDialog->setOption(QFileDialog::ShowDirsOnly);
		pDialog->show();
		pDialog->setAttribute(Qt::WA_DeleteOnClose);

		connect(pDialog, SIGNAL(fileSelected(QString)), this, SLOT(ChooseFolder(QString)));
		return;
	}
	
	QDir theFolder(folderPath);
	// if the folder doesn't exists, offer to create it
	if(!theFolder.exists()) {
		QMessageBox msgBox;
		msgBox.setIcon(QMessageBox::Question);
		QString strMess("The folder %1 doesn't exist.");
		strMess = strMess.arg(folderPath);
		msgBox.setText(strMess);
		msgBox.setInformativeText("Do you want to create it?");
		msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::Cancel);
		msgBox.setDefaultButton(QMessageBox::Yes);
		int ret = msgBox.exec();
		if(ret == QMessageBox::Yes) {
			theFolder.mkpath(folderPath);
		}
	}
	if(folderPath != m_FolderPath)
		if(theFolder.exists())
			m_FolderPath = folderPath;
}

void GPlainTextLogger::EventBucketUpdated()
{
	if(m_ShouldLogOnUpdate)
		AppendLine();
}

void GPlainTextLogger::EventTimerFired()
{
	if(m_ShouldLogOnTimer) {
		AppendLine();
	}
}

void GPlainTextLogger::AppendLine()
{
	QList<GParam*> parmToLog = m_Bucket.Params();
	QList<GParam*> parmNames = m_BucketColNames.Params();
	GVectorDouble valuesToLog = m_Bucket.DoubleValues();

	QFile file(FilePath());
	if(!file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
		return;

	QTextStream out(&file);
	out.setRealNumberPrecision(10);

	// if it is the first line, we memorize the time and set it as the origin of time
	if(m_UpdateCount == 0) {
		m_OriginTime = QDateTime::currentDateTime();
		// and we add a line with some name
		
		//SPECIAL FIRST COLUMN NAMES: Bart 2016-04-19. 
		//out << m_FirstColName << "\t"; //previous first column, removed. 
		out << "Update\t";// update index.
		out << "Elapsed time\t";// elapsed time (previously "sec update") 
		out << "UTC\t";// UTC time in ms, time zone adjusted?
		out << "Local date\t";// Local date.
		out << "Local time\t";// Local time (24 hour formal).

		foreach(GParam* pPar, parmToLog) {
			// is there is a name provided in the name bucket, we use this one
			GParamString* pParStr = qobject_cast<GParamString*>(parmNames.value(parmToLog.indexOf(pPar)));
			if(pParStr)
				out << pParStr->StringValue() << "\t";
			else
				out << pPar->Name() << "\t";
		}
		out << "\n";
		// and we add a line with some units

		//SPECIAL FIRST COLUMN UNITS: Bart 2016-04-19. 
		//out << m_FirstColValue.Units() << "\t"; //previous first column, removed. 
		out << "\t";// update index.
		out << "s\t";// elapsed time (previously "sec update") 
		out << "ms\t";// UTC time in ms, time zone adjusted?
		out << "MM/dd/yyyy\t";// Local date, OriginPro format.
		out << "HH:mm:ss.###\t";// Local time (24 hour format), OriginPro format.

		foreach(GParam* pPar, parmToLog) {
			// is there is a name provided in the name bucket, we use this one
			out << pPar->Units() << "\t";
		}
		out << "\n";
	}
	QDateTime thedatetime = QDateTime::currentDateTime();// local system clock time. 
	qint64 msSinceStart = m_OriginTime.msecsTo(thedatetime);
	qint64 msSinceMidnight = QDateTime(m_OriginTime.date()).msecsTo(thedatetime);
	qint64 msSinceEpoch = thedatetime.toMSecsSinceEpoch(); //UTC time in ms, but might have time zone adjust? 
	//qDebug() << thedatetime.toMSecsSinceEpoch();//UTC in ms, such as 1460992218058. 
	//qDebug() << thedatetime.toTime_t();//UTC in s, such as 1460992218. 
	m_SecUpdate = double(msSinceStart) / 1e3;
	m_SecMidnight = double(msSinceMidnight) / 1e3;
	m_SecEpoch = double(msSinceEpoch) / 1e3;
	m_CurrentIndexUpdate = m_UpdateCount;

	//2016-04-18 Bart commented out, because really want to making special first columns permanent: 
//  	GMathScriptEngine firstColumnEngine;
// 	firstColumnEngine.globalObject().setProperty("tu", double(m_SecUpdate));
// 	firstColumnEngine.globalObject().setProperty("tm", double(m_SecMidnight));
// 	firstColumnEngine.globalObject().setProperty("t", double(m_SecEpoch));
// 	firstColumnEngine.globalObject().setProperty("i", int(m_CurrentIndexUpdate));
// 	QScriptValue theValue = firstColumnEngine.evaluate(m_FirstColFormula);
// 	if(!m_FirstColFormula.StringValue().isEmpty())
// 		m_FirstColValue = theValue.toNumber();
// 
// 	out << m_FirstColValue.DoubleValue() << "\t";

	//SPECIAL FIRST COLUMNS BEFORE DATA:  Bart 2016-04-19. 
	out << m_CurrentIndexUpdate.DoubleValue() << "\t";// update index.
	out << m_SecUpdate.DoubleValue() << "\t";// elapsed time (previously "sec update") 
	//out << m_SecEpoch.DoubleValue() << "\t";// UTC time in s, time zone adjusted? DON'T USE BECAUSE MISSING ms information.
	out << msSinceEpoch << "\t";// UTC time in ms, time zone adjusted? USE THIS. 
	out << thedatetime.toString("MM/dd/yyyy") << "\t";// Local date.
	out << thedatetime.toString("hh:mm:ss.zzz") << "\t";// Local time (24 hour format).

	foreach(double iVal, valuesToLog)
		out << iVal << "\t";
	out << "\n";
	m_UpdateCount++;
}

void GPlainTextLogger::OpenLogFile()
{
	if(m_pNotePadProcess) {
		m_pNotePadProcess->close();
		m_pNotePadProcess->deleteLater();
	}
	m_pNotePadProcess = new QProcess(this);
	m_pNotePadProcess->start("notepad", QStringList(FilePath()));
}

QString GPlainTextLogger::FilePath()
{
	QString fileCompletePath = m_FolderPath;
	fileCompletePath += "\\";
// 	fileCompletePath += QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss.zzz");
	fileCompletePath += m_FileName;
	fileCompletePath += ".txt";
	fileCompletePath.replace(".txt.txt", ".txt");

	return fileCompletePath;
}

void GPlainTextLogger::OpenFolder()
{
	QProcess *myProcess = new QProcess(this);
	QFileInfo theFileInfo(FilePath());
	QString path = theFileInfo.absoluteDir().path();
	path.replace("/", "\\");
	myProcess->start("explorer", QStringList(path));
}

void GPlainTextLogger::TrashContent()
{
	RenameLogFile("trash");
}

void GPlainTextLogger::RenameLogFile( QString newFileName /*= ""*/ )
{
	// starting a new file, reseting the count
	ResetCount();
	// open the file
	QFile TheActualLogFile(FilePath());
	if(!TheActualLogFile.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
		return;
	QFileInfo theFileInfo(TheActualLogFile);
	QDir theDir = theFileInfo.absoluteDir();
	QString baseName = theFileInfo.completeBaseName();

	bool ok = true;
	// if we don't provide a newFileName, a dialog asks for it
	if(newFileName == "")
        newFileName = QInputDialog::getText(nullptr, tr("Rename file"), tr("This will overwrite any existing file with the same name:"), QLineEdit::Normal, "new name", &ok);

	if(!ok || newFileName.isEmpty() || baseName.isEmpty())
		return;
	// the newFileName with the path and extension
	QString pathandfilename = FilePath();
	pathandfilename.replace(baseName, newFileName);
	// let's remove the new file if it exists
	theDir.remove(pathandfilename);
	// then we can rename
	TheActualLogFile.rename(pathandfilename);
}

void GPlainTextLogger::SetTimerLapse( double inSec )
{
	m_Timer.setInterval(int(inSec * 1000.0));
}

void GPlainTextLogger::ResetCount()
{
	m_UpdateCount = 0;
// 	m_CurrentIndexUpdate = m_UpdateCount;
// 	m_SecUpdate = 0;
}

QWidget* GPlainTextLogger::ProvideNewExtraSettingsWidget( QWidget* parentWidget )
{
	QWidget* pWid = new QWidget(parentWidget);
	QFormLayout* pLay = new QFormLayout(pWid);
	pLay->addRow(m_FirstColName.ProvideNewLabel(pWid), m_FirstColName.ProvideNewParamLineEdit(pWid));
	pLay->addRow(new QLabel("First Column Values\n(i=index, t=time[ms])", parentWidget), m_FirstColFormula.ProvideNewParamLineEdit(pWid));
	return pWid;
}

void GPlainTextLogger::ShowExtraSettingsWidget()
{
    QWidget* pWid = ProvideNewExtraSettingsWidget(nullptr);
	// for clean-up
	pWid->setAttribute(Qt::WA_DeleteOnClose, true);
	pWid->setWindowFlags(Qt::Popup);
	pWid->show();
	pWid->adjustSize();
}
