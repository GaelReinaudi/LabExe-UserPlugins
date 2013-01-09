#include "sdfghjk.h"
#include <QList>

//constructor for sdfghjk class which inherits QMainWindow class
sdfghjk::sdfghjk(QWidget *parent, Qt::WFlags flags)
	: QMainWindow(parent, flags)
	, m_CliosOrigin(this)
{
	//makes the button
	ui.setupUi(this);
	//connect Open Origin and Send Data to OpenOrigin() and SendData() functions, respectively
	connect(ui.pOpenOriginButton, SIGNAL(clicked()), &m_CliosOrigin, SLOT(OpenOrigin()));
	connect(ui.pSendDataButton, SIGNAL(clicked()), this, SLOT(SendData()));

	
}

sdfghjk::~sdfghjk()
{

}

void sdfghjk::SendData()
//this function appends lines of 1s to a specified worksheet
{
	unsigned int nRowStart = -1; //-1 means append at the end (from SendNumericDataToWksDlg)

	//make QList of doubles and put 1s inside
	QList<double> line;
	for (int i=0; i<3; i++)
	{
		line.append(1);
	}

	//set qstrWksName equal to the text in the lineEdit on the Qt window
	QString qstrWksName = ui.lineEdit->text();

	//check to see if worksheet already exists, and create worksheet if it does not exist
	if (m_CliosOrigin.CheckWorksheetExistence(qstrWksName) == false)
	{
		m_CliosOrigin.CreateWorksheet(qstrWksName);
	}

	m_CliosOrigin.AppendLineToWorksheet(qstrWksName, line, nRowStart);

}