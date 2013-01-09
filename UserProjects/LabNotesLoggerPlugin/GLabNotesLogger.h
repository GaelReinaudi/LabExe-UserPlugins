#ifndef GLabNotesLogger_H
#define GLabNotesLogger_H

#include "device.h"
#include "param.h"
//#include <sstream>//convert numbers to strings easily.
/////////////////////////////////////////////////////////////////////
//! \brief The GLabNotesLogger class implements a GProgDevice.
/*!
This soft device allows you to define an input parameter by drag-and-dropping it in a param-bucket. 
When the input is updated, the average over the past \e n values is calculated and displayed at the output. 
The value of \e n is defined by a spin-box.
If there are not yet \e n values in the past history of the parameter, the average is made on all existing data. 
The reset button clears the history of the parameter.
*/
//[inheritance]
class GLabNotesLogger : public GProgDevice
//[inheritance]
{
	Q_OBJECT

public:

//[constructor]
	//! Constructor
	GLabNotesLogger(QObject *parent, QString uniqueIdentifierName = "");
//[constructor]
	~GLabNotesLogger();

public slots:
	//! Commit button calls this to save new notes from user input to today's file. 
	void Commit();
	//! Settings button calls this to give a Settings popup window. 
	void Settings();
	//! Settings dialog box Ok button triggers this.
	void SettingsOk();
	//! Settings dialog box Cancel button triggers this.
	void SettingsApply();
	//! Settings dialog box Apply button triggers this.
	void SettingsCancel();
	//! Today button calls this to setup a new Lab Notes file. 
	void NewDay();
	//! Expt. Params button calls this to print experimental parameters to file. 
	void ExptParams();
	//! Browse button calls this in Settings dialog box, to manually pick new file.  
	void Browse();

//![PopulateDeviceWidget]
protected:
	//! Re-implemented to provide a new widget adequately connected to this GLabNotesLogger.
	void PopulateDeviceWidget(GDeviceWidget* theDeviceWidget);
//![PopulateDeviceWidget]

//! [variables]
private:
	GParamString m_Destination;//Default directory path with filename from user (can have date characters).
	GParamString m_Path;//Actual path to file (interpreted from m_Destination).
	GParamString m_NewNote;//Text input from user.
	GParamString m_OldNotes;//File contents (old user input). 

	QTextEdit* oldTextEdit;
	QTextEdit* newTextEdit;
	
	//! Settings dialog box variables:
	QDialog* m_Dialog;
	QLineEdit* destinationLineEdit;
	QLineEdit* pathLineEdit;
	GParamBucket m_ExptParams;
	GParamString m_CurrentDirectory;//! Current directory (for sharing with other plugins).
	GParamBucket m_CurrDirBucket;

private slots:
	void InitSavedSettings();
	void UpdateOldNotes();
};

#endif // GLabNotesLogger_H
