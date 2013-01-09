#include "GClioOrigin.h"
#include <QDebug>
#include "atlsafe.h"
#include <QByteArray>
#include <QList>
#include <QVariant>
#include <ActiveQt\qaxtypes.h>

GClioOrigin::GClioOrigin(QObject *parent)
	: QObject(parent)
	, pMyOriginClient(0)   //intialize pointer to 0
{

}

GClioOrigin::~GClioOrigin()
{
	//close Origin when the program closes
	if(pMyOriginClient != 0) {
		delete pMyOriginClient;
		pMyOriginClient = 0;
	}
}

void GClioOrigin::OpenOrigin()
//from SendNumericDataToWksDlg.cpp
{

	pMyOriginClient = new COriginClient(1);

	//apply the show Origin window option
	OnShowOriginWindow();
	
 
}

void GClioOrigin::CreateWorksheet(QString wksName)
{

	//convert the QString into _bstr_t (from google)
	std::string str;
	str = wksName.toStdString();
	_bstr_t s;
	s = str.c_str();

	//create worksheet page (from SendNumericDataToWksDlg)
	_bstr_t bstr = pMyOriginClient->operator ->()->CreatePage(ORIGIN_WINTYPE_WKS, _bstr_t(s), _bstr_t("w"));

}

void GClioOrigin::OnShowOriginWindow()
//from SendNumericDataToWksDlg
{
	pMyOriginClient->operator->()->Visible = OrgApplication::MAINWND_SHOW_BRING_TO_FRONT;
}

void GClioOrigin::AppendLineToWorksheet(QString wksName, QList<QVariant> data, int nRowStart)
{

	//convert QString to LPCSTR (found by google searching)
	std::string str;
	str = wksName.toStdString();
	LPCSTR lstrWksName;
	lstrWksName = str.c_str();

	//convert first QList into a QVariant (QT Assistant)
	QVariant qvarData(data);

	//put QList data inside new QList to make it horizontal and then convert horizontal QList to QVariant
	QList<QVariant> line;

	line.append(qvarData);

	QVariant qvarLine(line);

	//convert QVariant to VARIANT
	VARIANT var;

	QVariantToVARIANT(qvarLine, var);

	//append line to worksheet (from SendNumericDataToWksDlg)
	pMyOriginClient->SetWorksheet(lstrWksName, var, nRowStart);


}

void GClioOrigin::AppendLineToWorksheet(QString wksName, QList<double> data, int nRowStart)
//this function is used when the QList is of doubles rather than QVariants
{
	//convert QList<double> to QList<QVariant>
	QList<QVariant> qvarData;
	for (int i=0; i<data.size(); i++)
	{
		QVariant qvar(data[i]);
		qvarData.append(qvar);
	}

	AppendLineToWorksheet(wksName, qvarData, nRowStart);
}

bool GClioOrigin::CheckWorksheetExistence(QString wksName)
{
	//Convert QString to _bstr_t (found by google searching)
	std::string str;
	str = wksName.toStdString();
	_bstr_t s;
	s = str.c_str();

	//check if worksheet exists using commands from SendNumericDataToWksDlg
	WorksheetPtr pwks = pMyOriginClient->operator ->()->FindWorksheet(_bstr_t(s));

	if (pwks == NULL)
	{
		return false;
	}
	else
	{
		return true;
	}
}