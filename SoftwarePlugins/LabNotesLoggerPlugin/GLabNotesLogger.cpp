#include "GLabNotesLogger.h"

//! [Initialize the parameters]
GLabNotesLogger::GLabNotesLogger(QObject *parent, QString uniqueIdentifierName /* = "" */)
	: GProgDevice(parent, uniqueIdentifierName)
	, m_Destination("Destination", this, GParam::ReadOnly)
	, m_Path("Path", this, GParam::ReadOnly)
    , m_NewNote("New Note", this)
    , m_OldNotes("Old Notes", this, GParam::ReadOnly)
    , m_ExptParams("Experimental parameters to print", this, GParam::ReadOnly)
	, m_CurrentDirectory("Current Directory", this, GParam::ReadOnly)
	, m_CurrDirBucket("Current Directory Bucket", this, GParam::ReadOnly)
{
//! [Initialize the parameters]
/*
Note: All parameters defined with "this" device as parent (see above) will be saved automatically 
when the device state is saved to file. The name used to save the values is the same as the one provided 
for the name (the first argument, e.g. "num. samples").
*/
//! [Extra initialization the parameters]
	// Default value of the sample size for the first use.
	// It will be over-written if a previously saved value is read from a file.
	m_Destination = "F:/Data/yyyy/MM-MMM/yyyy-MM-dd_LabNotes.txt";
	//FreedomFries current convention: "F:\Data\yyyy\MM-MMM\yyyy-MM-dd_LabNotes.txt";
	//Troubleshooting: "C:/Users/Public/Desktop/yyyy/MM-MMM/yyyy-MM-dd_LabNotes.txt"
	m_Path = "";
	m_NewNote = "(type here)";
	m_OldNotes = "(no file yet)";
	m_CurrentDirectory = "";
	m_CurrDirBucket.Freeze(true);// Do not want drag/drop of new variables in this bucket. 

	// Connections:  
	// -- After saved GParam values are loaded, make sure propagate changes from default values: 
	connect(this, SIGNAL(ParamJustInterpretSettings()), this, SLOT(InitSavedSettings()));
}
//! [Extra initialization the parameters]

GLabNotesLogger::~GLabNotesLogger()
{

}

/////////////////////////////////////////////////////////////////////
/*!
Populates a widget provided by a workbench in order to represent (and be adequately connected to) this GLabNotesLogger. 
Layouts are used to make the widget react correctly to re-sizing.
The easiest way to connect the button and spinboxes to the actual instance of the corresponding parameter 
is to use the method GParamXXXX::ProvideNew----Widget(), that does all the necessary connections 
automatically (which would be the equivalent of this PopulateDeviceWidget(), but for a single parameter).
\param:  GDeviceWidget * theDeviceWidget : the parent widget in the gui.
*////////////////////////////////////////////////////////////////////
//[PopulateDeviceWidgetImplementation]
void GLabNotesLogger::PopulateDeviceWidget(GDeviceWidget* theDeviceWidget )
{	// == Assemble Main Layout ==

	// Create widgets...
	// Text box to display previous notes / file contents. 
	oldTextEdit = new QTextEdit();
	oldTextEdit->setText("(no file yet)");//setText(m_OldNotes.StringValue());
	oldTextEdit->setReadOnly(true);//Not user editable!
	// Text box to let user draft new text, which can be appended to file. 
	newTextEdit = new QTextEdit;
	newTextEdit->setMaximumHeight(80);
	newTextEdit->setText("(type here)");//setText(m_NewNote.StringValue());
	// Buttons
	QPushButton* newDayButton = new QPushButton(tr("Today"));
	QPushButton* specialButton = new QPushButton(tr("Settings"));
	//QPushButton* timeStampButton = new QPushButton(tr("Print time"));
	QPushButton* exptParamsButton = new QPushButton(tr("Print Expt"));
	QPushButton* commitButton = new QPushButton(tr("&Commit"));
	connect(commitButton, SIGNAL(clicked()), this, SLOT(Commit()));
	connect(specialButton, SIGNAL(clicked()), this, SLOT(Settings()));
	connect(newDayButton, SIGNAL(clicked()), this, SLOT(NewDay()));
	connect(exptParamsButton, SIGNAL(clicked()), this, SLOT(ExptParams()));
	
	// Arrange widgets...
	QHBoxLayout* pHlay = new QHBoxLayout();
	QVBoxLayout* pVlay1 = new QVBoxLayout();
	pVlay1->addWidget(oldTextEdit);
	pVlay1->addWidget(newTextEdit);
	QDialogButtonBox* boxButtons = new QDialogButtonBox(Qt::Vertical);
	boxButtons->addButton(newDayButton, QDialogButtonBox::ActionRole);
	boxButtons->addButton(specialButton, QDialogButtonBox::ActionRole);
	boxButtons->addButton(exptParamsButton, QDialogButtonBox::ActionRole);
	//boxButtons->addButton(timeStampButton, QDialogButtonBox::ActionRole);
	boxButtons->addButton(commitButton, QDialogButtonBox::ActionRole);
	pHlay->addLayout(pVlay1);
	pHlay->addWidget(boxButtons);
	theDeviceWidget->AddSubLayout(pHlay);

	// == Assemble Special pop-up dialog window ==
	//Let the user pick parent directory, folder format, filename formats.
	//Tabs: 
	//	(a) File Setup: allows browsing and opening manual files with QFileDialog
	//		Allows user to modify path or destination. Gives current directory as GParam. 
	//	(b) Expt. Parameters: allow user to put GParams into a multi-param bucket, so 
	//		all their values can be captured and printed in the new note area. 
	//		Want to make it easier to capture all relevant experimental parameters. 
	m_Dialog = new QDialog(theDeviceWidget);
	// -- Setup Ok, Apply, and Cancel buttons: 
	QDialogButtonBox* DialogButtons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Apply | QDialogButtonBox::Cancel);
	connect(DialogButtons, SIGNAL(accepted()), this, SLOT(SettingsOk()));
	connect(DialogButtons->button(QDialogButtonBox::Apply), SIGNAL(clicked()), this, SLOT(SettingsApply()));
	connect(DialogButtons, SIGNAL(rejected()), this, SLOT(SettingsCancel()));
	// -- Setup General, Scaling, and Display tabs:  
	QTabWidget* tabWidget = new QTabWidget;
	QDialog* FileTab = new QDialog(tabWidget);
	QDialog* ExptTab = new QDialog(tabWidget);
	tabWidget->addTab(FileTab, tr("File Setup"));
	tabWidget->addTab(ExptTab, tr("Print Expt Setup"));
	// -- Setup layout for the dialog box:
	QVBoxLayout* dialogLayout = new QVBoxLayout;
    dialogLayout->setSizeConstraint(QLayout::SetNoConstraint);
    dialogLayout->addWidget(tabWidget);
    dialogLayout->addWidget(DialogButtons);
	m_Dialog->setLayout(dialogLayout);
    m_Dialog->setWindowTitle(tr("GLabNotesLogger Settings"));

	// -- Setup the File Setup tab: 
	//QGridLayout* FileTabLayout = new QGridLayout;
	QVBoxLayout* FileTabVLayout = new QVBoxLayout;
	QGroupBox* defaultFileBox = new QGroupBox(tr("Default settings"));
	QGroupBox* manualFileBox = new QGroupBox(tr("Manual override"));
	//QGridLayout* defaultFileGrid = new QGridLayout;
	//QGridLayout* manualFileGrid = new QGridLayout;
	QFormLayout* defaultFileForm = new QFormLayout;
	QFormLayout* manualFileForm = new QFormLayout;
	// -- Default settings box: 
	QLabel* destinationLabel = new QLabel(tr("Default path format:"));
	destinationLineEdit = new QLineEdit;
	destinationLineEdit->setText(m_Destination.StringValue());
	
	//defaultFileGrid->addWidget(destinationLabel,0,0);
	//defaultFileGrid->addWidget(destinationLineEdit,0,1);
	//defaultFileBox->setLayout(defaultFileGrid);
	defaultFileForm->addRow(destinationLabel);
	defaultFileForm->addRow(destinationLineEdit);
	//defaultFileForm->addRow(pCurrentDirWid);
	defaultFileBox->setLayout(defaultFileForm);
	// -- Manual override box: 
	QLabel* pathLabel = new QLabel(tr("Current path:"));
	pathLineEdit = new QLineEdit;
	pathLineEdit->setText(m_Path.StringValue());
	QPushButton* manualFileButton = new QPushButton(tr("Browse"));
	connect(manualFileButton, SIGNAL(clicked()), this, SLOT(Browse()));
	//manualFileGrid->addWidget(pathLabel,0,0);
	//manualFileGrid->addWidget(pathLineEdit,0,1);
	//manualFileBox->setLayout(manualFileGrid);
	manualFileForm->addRow(pathLabel);
	manualFileForm->addRow(pathLineEdit);
	manualFileForm->addRow(manualFileButton);
	manualFileBox->setLayout(manualFileForm);
	// -- finish assembling the File Setup tab
	//FileTabLayout->addWidget(defaultFileBox,1,0,6,2);
	//FileTabLayout->addWidget(manualFileBox,7,0,4,2);
	//FileTab->setLayout(FileTabLayout);
	FileTabVLayout->addWidget(defaultFileBox);
	FileTabVLayout->addWidget(manualFileBox);
	// -- Add GParam to output the current directory:  
	GParamBucketWidget* pCurrentDirWid = m_CurrDirBucket.ProvideParamBucketWidget(theDeviceWidget);
	pCurrentDirWid->setTitle("");
	m_CurrDirBucket.AddParam(&m_CurrentDirectory);
	FileTabVLayout->addWidget(pCurrentDirWid);
	FileTab->setLayout(FileTabVLayout);
	
	// -- Setup the Print Expt tab: 
	// Just add a GParamBucket here, for user to drag in settings to capture. 
	QVBoxLayout* ExptTabVLayout = new QVBoxLayout();
	ExptTab->setLayout(ExptTabVLayout);
	GParamBucketWidget* pEPWid = m_ExptParams.ProvideParamBucketWidget(theDeviceWidget);
	pEPWid->UseHighLightDecay(false);
	ExptTabVLayout->addWidget(pEPWid);
	// -- Insert an expandable space
	ExptTabVLayout->addStretch();
}
//[PopulateDeviceWidgetImplementation]

void GLabNotesLogger::InitSavedSettings()
{	//This runs once after saved GParam values are loaded, to make sure 
	//that the saved values are used from the start.  
	//m_Destination = "C:/Users/Public/Desktop/yyyy/dd-MMM/yyyy-dd-MM_LabNotes.txt";

	//If there's a saved file, setup old and new notes: 
	if(m_Path.StringValue()!="")
	{	UpdateOldNotes();
		m_NewNote = "";
		newTextEdit->setText(m_NewNote);
	}
}

void GLabNotesLogger::Commit()
{	//Append m_NewNote to the end of the current file, errors permitting.  
	
	//Get the user's input:  
	m_NewNote = newTextEdit->toPlainText();
	
	//NOTE: We accept m_NewNote="", so Commit() can add line returns to the file.  

	QFile file(m_Path.StringValue());
	if(file.open(QIODevice::WriteOnly | QIODevice::Text | QIODevice::Append))
	{	QTextStream stream(&file);
		//jump to end of file
		stream.seek(file.size());
		stream << "\n" << m_NewNote;//NOTE: Append feature above makes this not overwrite file.
		file.close();

		//Let the user know by erasing m_NewNote, refreshing m_OldNotes:
		m_NewNote = "";
		UpdateOldNotes();
	}
	else
	{	//Hmm, couldn't open the file.
		//Alert user by not erasing m_NewNote...
	}
	//Update m_NewNote.
	newTextEdit->setText(m_NewNote.StringValue());
}

void GLabNotesLogger::NewDay()
{	//User wants a new text file (and folders) created to match the format
	//given in m_Destination, and to prep this new file for use by this LabExe Plugin. 

	//First, update the path for today's date:
	m_Path = QDate::currentDate().toString(m_Destination);

	//Get the filename:
	QString filename = QDir(m_Path.StringValue()).dirName();
	//Also, get the directory path to the file: 
	QString filepath = m_Path.StringValue();
	filepath.remove(filename);
	
	//Error check the path -- is the filename blank?
	if(filename=="")
	{	//Warn the user and abort:
		QMessageBox(QMessageBox::Warning,"LabNotesLogger","I'm sorry Dave, but I can't make a file without a name.").exec();
		return;//stop NewDay()
	}

	//Make the directory path, if it doesn't already exist: 
	if(!QDir().mkpath(filepath))
	{	//Warn the user that you couldn't make the directory path:
		QMessageBox(QMessageBox::Warning,"LabNotesLogger","I'm sorry Dave, but I can't make this path: "+filepath).exec();
		return;//stop NewDay()
	}
	
	//See if the file already exists: 
	QFile file(m_Path.StringValue());
	if(file.exists())
	{	//File exists!  
		//QMessageBox(QMessageBox::Warning,"LabNotesLogger","Dave, did you know that today's file already exists?").exec();
	}
	else
	{	//File doesn't exist yet, so let's create it and set it up: 
		if(file.open(QIODevice::ReadWrite | QIODevice::Text))
		{	//Hooray, created the file.  
			//Now give it a useful header: 
			QTextStream stream(&file);
			stream<<"% [ This file ("<<filename<<") was started by the LabExe LabNotesLogger Plugin on ";
			stream<<QDate::currentDate().toString("MM/dd/yyyy")<<" at "<<QTime::currentTime().toString("hh:mm")<<". ]\n";
			stream<<"== "<<QDate::currentDate().toString("yyyy-MM-dd (ddd)")<<" Lab Notes ==";
			file.close();
		}
		else
		{	//Hmm, couldn'y create the file.  Complain to user. 
			QMessageBox(QMessageBox::Warning,"LabNotesLogger","I'm sorry Dave, but I can't make this file: "+filename).exec();
			return;
		}
	}

	//Update m_OldNotes with file's contents: 
	UpdateOldNotes();
	
	//Update the path in the Settings dialog box: 
	pathLineEdit->setText(m_Path.StringValue()); 

	//Update the current directory: 
	m_CurrentDirectory = filepath;
}

void GLabNotesLogger::UpdateOldNotes()
{	//Populate m_OldNotes with the last 100 lines of the current file. 
	QFile file(m_Path.StringValue());
	if(file.open(QIODevice::ReadWrite | QIODevice::Text))
	{	//If the file isn't too huge, upload it: 
		if(file.size()<=Q_INT64_C(10000000))
		{	QTextStream stream(&file);
			stream.seek(0);//make sure at beginning of file
			m_OldNotes = stream.readAll();
			//m_OldNotes = QString::number(file.size());//show the file size (debugging)
		}
		else
		{	m_OldNotes = "(file's too big!)";	
		}
		file.close();
	}
	else
	{	//Hmm, couldn't read the file.
		m_OldNotes = "(no file)";
	}

	//Share with the user: 
	oldTextEdit->setText(m_OldNotes.StringValue());
	//Scroll to the bottom: 
	oldTextEdit->moveCursor(QTextCursor::End);
}

void GLabNotesLogger::Settings()
{	//Restore all the values in the Settings dialog box to previous values: 
	destinationLineEdit->setText(m_Destination.StringValue());
	pathLineEdit->setText(m_Path.StringValue());

	//Show the Settings dialog window. 
	m_Dialog->show();
}
void GLabNotesLogger::SettingsOk()
{	//Apply changes:
	SettingsApply();

	//Close the Settings dialog window. 
	m_Dialog->hide();	
}
void GLabNotesLogger::SettingsApply()
{	//Save changes:
	m_Destination = destinationLineEdit->text();
	m_Path = pathLineEdit->text();
	m_CurrentDirectory = m_Path.StringValue().remove(QDir(m_Path.StringValue()).dirName());//This assumes m_Path has a filename at its end. 
	
	//Update the old notes to reflect the actual path. 
	UpdateOldNotes();
}
void GLabNotesLogger::SettingsCancel()
{	//Restore all the values in the Settings dialog box to previous values: 
	destinationLineEdit->setText(m_Destination.StringValue());
	pathLineEdit->setText(m_Path.StringValue());

	//Close the Settings dialog window. 
	m_Dialog->hide();
}

void GLabNotesLogger::ExptParams()
{	//Capture list of GParam* pointers to parameters in the bucket: 
	QList<GParam*> toPrint = m_ExptParams.Params();
	
	if(toPrint.size()==0)
	{	//If no parameters to report, do nothing and exit. 
		return;
	}
	
	//Print settings to m_NewNote: 
	//--capture current user input (to be polite and not delete it):  
	m_NewNote = newTextEdit->toPlainText();
	//(not file, so user can edit it as needed)
	GParam* dummy;
	m_NewNote = m_NewNote + "===Experimental parameters at "+QTime::currentTime().toString("hh:mm")+"===\n";
	for(int i=0; i<toPrint.size(); i++)
	{	dummy = toPrint.at(i);
		//Format: "*Name [Units]: Value\n"
		if(dummy->Units()=="")//Are units defined?
		{	m_NewNote = m_NewNote+"*"+dummy->Name()+": "+dummy->StringContent()+";\n";
		}
		else//No units: 
		{	m_NewNote = m_NewNote+"*"+dummy->Name()+" ["+dummy->Units()+"]: "+dummy->StringContent()+";\n";
		}
	}

	//Update m_NewNote.
	newTextEdit->setText(m_NewNote.StringValue());
}
void GLabNotesLogger::Browse()
{	QString test = QFileDialog::getOpenFileName(m_Dialog,tr("New path"), m_Path, tr("Text files (*.txt)"));
	if(test!="")
	{	//User selected a new text file, so temporarily store it in the QLineEdit for m_Path: 
		pathLineEdit->setText(test);
		//To actually use this new path, the user has to now click Ok or Apply.  		
	}
}
