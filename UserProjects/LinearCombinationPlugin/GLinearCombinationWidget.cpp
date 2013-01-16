#include "StdAfx.h"
#include "GLinearCombinationWidget.h"
#include "GLinearCombination.h"

GLinearCombinationWidget::GLinearCombinationWidget(GLinearCombination* pTheLinearCombination, QWidget *parent)
	: QWidget(parent)
	, m_pLinComb(pTheLinearCombination)
{
	setupUi(this);
	if(!m_pLinComb)
		return;

	pLayoutInput->addWidget(m_pLinComb->m_BucketInput.ProvideNewParamWidget(this));
	pLayoutOutput->addWidget(m_pLinComb->m_BucketOutput.ProvideNewParamWidget(this));

	pTableView->setModel(&m_pLinComb->m_MatrixModel);

//	connect(pTableView, SIGNAL(clicked(QModelIndex)), this, SLOT(OpenPersistentTableEditor(QModelIndex)));

// 	// resizing the columns when an input is added
//	connect(&m_pLinComb->m_BucketInput, SIGNAL(ParamAdded(GParam*)), pTableView, SLOT(resizeColumnsToContents()), Qt::QueuedConnection);
	connect(&m_pLinComb->m_BucketOutput, SIGNAL(ParamAdded(GParam*)), pTableView, SLOT(resizeRowsToContents()), Qt::QueuedConnection);
}

GLinearCombinationWidget::~GLinearCombinationWidget()
{

}

void GLinearCombinationWidget::OpenPersistentTableEditor(QModelIndex theIndex)
{
	pTableView->openPersistentEditor(theIndex);
}