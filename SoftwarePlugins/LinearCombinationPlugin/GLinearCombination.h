#ifndef GLINEARCOMBINATION_H
#define GLINEARCOMBINATION_H

#include "device.h"
#include "param.h"

class GLinearCombination : public GProgDevice
{
	Q_OBJECT

public:
	GLinearCombination(QObject *parent, QString uniqueIdentifierName = "");
	~GLinearCombination();

protected:
	//! Re-implemented
	void PopulateSettings(QSettings& inQsettings);
	//! Re-implemented
	void InterpretSettings(QSettings& fromQsettings);
	//! Re-implemented
	void DelayedInterpretSettings(QSettings& fromQsettings);

public slots:
	//! Makes the linear combination to be evaluated and returned in the result param bucket
	void Evaluate();

protected:
	//! Re-implemented
	void PopulateDeviceWidget(GDeviceWidget* theDeviceWidget);

protected slots:
	//! Adds a column to the matrix. if pParam is given, it will try to use information on the position of the param in the bucket in order to insert the column at the good position
	void AddColumn(GParam* pParam = 0);
	//! Adds a row to the matrix. if pParam is given, it will try to use information on the position of the param in the bucket in order to insert the row at the good position
	void AddRow(GParam* pParam = 0);
	//! Removes a column from the matrix.
	void RemoveColumn(int indexColumn);
	//! Removes a row from the matrix.
	void RemoveRow(int indexRow);

private:
	//! returns the value in the (i, j) position of the matrix. 0 if none.
	double ValueMatrix( int i, int j );
	//! sets the value in the (i, j) position of the matrix.
	void SetValueMatrix(int i, int j, double newValue);

private:
	GParamBucket m_BucketInput;
	GParamBucket m_BucketOutput;
	//! the model that will hold the matrix data and communicate it to the tablewidget.
	QStandardItemModel m_MatrixModel;

	friend class GLinearCombinationWidget;
};

#endif // GLINEARCOMBINATION_H
