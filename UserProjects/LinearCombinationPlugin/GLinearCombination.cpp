#include "StdAfx.h"
#include "GLinearCombination.h"
#include "GLinearCombinationWidget.h"

GLinearCombination::GLinearCombination(QObject *parent, QString uniqueIdentifierName /*= ""*/)
	: GProgDevice(parent, uniqueIdentifierName)
	, m_BucketInput("Input", this)
	, m_BucketOutput("Output", this)
{
	m_BucketOutput.RemoveExtraField("trig");

	// connections to add or remove corresponding columns or rows
	connect(&m_BucketInput, SIGNAL(ParamAdded(GParam*)), this, SLOT(AddColumn(GParam*)));
	connect(&m_BucketInput, SIGNAL(ParamRemoved(int, GParam*)), this, SLOT(RemoveColumn(int)));
	// connections to add or remove corresponding columns or rows
	connect(&m_BucketOutput, SIGNAL(ParamAdded(GParam*)), this, SLOT(AddRow(GParam*)));
	connect(&m_BucketOutput, SIGNAL(ParamRemoved(int, GParam*)), this, SLOT(RemoveRow(int)));
}

GLinearCombination::~GLinearCombination()
{

}

void GLinearCombination::PopulateSettings( QSettings& inQsettings )
{
	GProgDevice::PopulateSettings(inQsettings);

	// the matrix
	inQsettings.beginWriteArray("col");
	for(int j = 0; j < m_MatrixModel.columnCount(); j++) {
		inQsettings.setArrayIndex(j);
		inQsettings.beginWriteArray("row");
		for(int i = 0; i < m_MatrixModel.rowCount(); i++) {
			inQsettings.setArrayIndex(i);
			inQsettings.setValue("v", ValueMatrix(i, j));
		}
		inQsettings.endArray();
	}
	inQsettings.endArray();

}

void GLinearCombination::InterpretSettings( QSettings& fromQsettings )
{
	GProgDevice::InterpretSettings(fromQsettings);

	LatterReadCurrentGroup(fromQsettings);
}

void GLinearCombination::DelayedInterpretSettings( QSettings& fromQsettings )
{
	GProgDevice::DelayedInterpretSettings(fromQsettings);
	// the matrix
	fromQsettings.beginReadArray("col");
	for(int j = 0; j < m_BucketInput.ParamCount(); j++) {
		fromQsettings.setArrayIndex(j);
		fromQsettings.beginReadArray("row");
		for(int i = 0; i < m_BucketOutput.ParamCount(); i++) {
			fromQsettings.setArrayIndex(i);
			SetValueMatrix(i, j, fromQsettings.value("v").toDouble());
		}
		fromQsettings.endArray();
	}
	fromQsettings.endArray();

	// only then one can connect to evaluate the output. Doing so in the constructor leads many evaluate during the construction of the matrix
	connect(&m_BucketInput, SIGNAL(BucketUpdatedValues()), this, SLOT(Evaluate()));
	connect(&m_MatrixModel, SIGNAL(itemChanged(QStandardItem*)), this, SLOT(Evaluate()));
}

void GLinearCombination::PopulateDeviceWidget(GDeviceWidget* theDeviceWidget )
{
	QBoxLayout* pLay = new QVBoxLayout();
	theDeviceWidget->AddSubLayout(pLay);

	GLinearCombinationWidget* pLinCombWid = new GLinearCombinationWidget(this, theDeviceWidget);
	pLay->addWidget(pLinCombWid);
}

void GLinearCombination::AddColumn( GParam* pParam /*= 0*/ )
{
	int indPar = m_BucketInput.IndexParam(pParam);
	if(indPar == -1) {
		qWarning() << "The parameter is not found in the bucket. 1476510";
		return;
	}
	if(!m_MatrixModel.insertColumn(indPar))
		return;

	// populate with 0
	for(int i = 0; i < m_MatrixModel.rowCount(); i++) {
		SetValueMatrix(i, indPar, 0.0);
	}
}

void GLinearCombination::AddRow( GParam* pParam /*= 0*/ )
{
	int indPar = m_BucketOutput.IndexParam(pParam);
	if(indPar == -1) {
		qWarning() << "The parameter is not found in the bucket. 1476511";
		return;
	}

	if(!m_MatrixModel.insertRow(indPar))
		return;

	// populate with 0
	for(int j = 0; j < m_MatrixModel.columnCount(); j++) {
		SetValueMatrix(indPar, j, 0.0);
	}
}

void GLinearCombination::RemoveColumn(int indexColumn)
{
	m_MatrixModel.removeColumn(indexColumn);
}

void GLinearCombination::RemoveRow(int indexRow)
{
	m_MatrixModel.removeRow(indexRow);
}

void GLinearCombination::Evaluate()
{
	// the input values
	GVectorDouble theInputDoubles = m_BucketInput.DoubleValues();
	// the output to be computed
	GVectorDouble theOutputDoubles;
	// we go through the items
	for(int i = 0; i < m_BucketOutput.ParamCount(); i++) {
		double iOutputVal = 0;
		for(int j = 0; j < m_BucketInput.ParamCount(); j++) {
			iOutputVal += theInputDoubles.value(j) * ValueMatrix(i, j);
		}
		theOutputDoubles.append(iOutputVal);
	}
	m_BucketOutput.SetValues(theOutputDoubles);
}

double GLinearCombination::ValueMatrix( int i, int j )
{
	QStandardItem* pItem = m_MatrixModel.item(i, j);
	if(!pItem) {
// 		qWarning() << "The item" << i << j << "in the matrix does not exist. Value will default to 0. 726290";
		return 0.0;
	}
	double itValue = pItem->data(Qt::DisplayRole).toDouble();
	return itValue;
}

void GLinearCombination::SetValueMatrix(int i, int j, double newValue)
{
	QStandardItem* pItem = m_MatrixModel.item(i, j);
	if(!pItem) {
//		qWarning() << "The item" << i << j << "in the matrix does not exist. 726291";
		pItem = new QStandardItem();
		m_MatrixModel.setItem(i, j, pItem);
	}
	pItem->setData(newValue, Qt::DisplayRole);
}