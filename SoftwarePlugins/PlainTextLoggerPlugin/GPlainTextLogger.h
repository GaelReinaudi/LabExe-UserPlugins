#ifndef GPLAINTEXTLOGGER_H
#define GPLAINTEXTLOGGER_H

#include "device.h"
#include "param.h"

class GPlainTextLogger : public GProgDevice
{
	Q_OBJECT

public:
	GPlainTextLogger(QObject *parent, QString uniqueIdentifierName = "");
	~GPlainTextLogger();

	//! Re-implemented
	QWidget* ProvideNewExtraSettingsWidget(QWidget* parentWidget);

public slots:
	//! Appends the parameters to the end of the file, ending by inserting a new line
	void AppendLine();

protected:
	//! Re-implemented
	void PopulateDeviceWidget(GDeviceWidget* theDeviceWidget);

protected slots:
	//! Assigns the working folder where the files will be written to. If folderPath is empty, pops up a dialog to select a folder
	void ChooseFolder(QString folderPath = "");
	//! Opens the log file
	void OpenLogFile();
	//! Opens the folder
	void OpenFolder();
	//! Trashes the content of the log file onto the file trash.txt of the same folder.
	void TrashContent();
	//! Shows a widget with extra settings
	void ShowExtraSettingsWidget();

private slots:
	//! Called when the bucket updated
	void EventBucketUpdated();
	//! Called when the timer fired
	void EventTimerFired();
	//! Sets the timer interval
	void SetTimerLapse(double inSec);
	//! Resets the count of update event. This will zero the first value of the column 1 of the file on the next update.
	void ResetCount();

private:
	//! Gives the file path
	QString FilePath();
	//! Renames the file (and overwrites an existing one if needed).
	void RenameLogFile(QString newFileName = "");

private:
	GParamBucket m_Bucket;
	GParamBucket m_BucketColNames;
	GParamBool m_ShouldLogOnUpdate;
	GParamBool m_ShouldLogOnTimer;
	GParamDouble m_SecondTimer;
	GParamString m_FolderPath;
	GParamString m_FileName;
	//! Timer for updating at fixed intervals
	QTimer m_Timer;

	//! first column name
	GParamString m_FirstColName;
	//! first column formula
	GParamString m_FirstColFormula;
	//! first column value after evaluation of the formula
	GParamDouble m_FirstColValue;

	//! count of updates within the file
	int m_UpdateCount;
	GParamDouble m_SecUpdate;
	GParamDouble m_SecMidnight;
	GParamDouble m_SecEpoch;
	GParamInt m_CurrentIndexUpdate;
	QProcess* m_pNotePadProcess;
	//! Origin of the time in the file written
	QDateTime m_OriginTime;
	friend class GPlainTextLoggerWidget;
};

#endif // GPLAINTEXTLOGGER_H
