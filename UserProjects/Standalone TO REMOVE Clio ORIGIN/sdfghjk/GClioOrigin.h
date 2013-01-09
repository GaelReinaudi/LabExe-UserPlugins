#ifndef GCLIOORIGIN_H
#define GCLIOORIGIN_H

#include <QObject>
#include "OriginClient.h"

class GClioOrigin : public QObject
{
	Q_OBJECT

public:
	GClioOrigin(QObject *parent);
	~GClioOrigin();

private:
	COriginClient* pMyOriginClient;

public:
	void OnShowOriginWindow();
	void AppendLineToWorksheet(QString wksName, QList<QVariant> data, int nRowStart);
	void AppendLineToWorksheet(QString wksName, QList<double> data, int nRowStart);
	void CreateWorksheet(QString wksName);
	bool CheckWorksheetExistence(QString wksName);

public slots:
	void OpenOrigin();

};

#endif // GCLIOORIGIN_H
