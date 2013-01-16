#include "GNumericalExpressionSettingsWidget.h"

#include <QCheckBox>
#include <QGroupBox>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QRadioButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include "GNumericalExpression.h"

GNumericalExpressionSettingsWidget::GNumericalExpressionSettingsWidget( GNumericalExpression* numericalExpression, QObject* parent /*= NULL*/)	
{
	m_NumericalExpression = numericalExpression;

	QGroupBox* pExpressionSettings = new QGroupBox;
	QBoxLayout* pExpressionSettingsLayout = new QVBoxLayout;
	QBoxLayout* pExpressionEditLayout = new QHBoxLayout;
	pExpressionSettings->setFixedWidth(400);
	pExpressionSettings->setTitle("Expression Settings");
	pExpressionSettings->setLayout(pExpressionSettingsLayout);
	pExpressionEditLayout->insertWidget(0, new QLabel("Expression:"), 0);
	pExpressionEditLayout->insertWidget(1, m_NumericalExpression->m_Expression.ProvideNewParamLineEdit(pExpressionSettings), 0);
	pExpressionSettingsLayout->insertLayout(0, pExpressionEditLayout);

	QGroupBox* pVariableSettings = new QGroupBox;
	QGroupBox* pShowVariables = new QGroupBox;
	QBoxLayout* pShowVariablesLayout = new QVBoxLayout;
	QBoxLayout* pVariableSettingsLayout = new QVBoxLayout;
	QRadioButton* pLayoutVariablesVertically = new QRadioButton;
	QRadioButton* pLayoutVariablesHorizontally = new QRadioButton;
	QRadioButton* pLayoutVariablesGrid = new QRadioButton;
	pVariableSettings->setFixedWidth(400);
	pVariableSettings->setTitle("Variable Settings");
	pVariableSettings->setLayout(pVariableSettingsLayout);
	pShowVariables->setTitle("Show Variables");
	pShowVariables->setCheckable(true);
	pShowVariables->setLayout(pShowVariablesLayout);
	pLayoutVariablesHorizontally->setText("Layout: Horizontal");
	pShowVariablesLayout->insertWidget(0, pLayoutVariablesHorizontally);
	pLayoutVariablesVertically->setText("Layout: Vertical");
	pShowVariablesLayout->insertWidget(1, pLayoutVariablesVertically);
	pLayoutVariablesGrid->setText("Layout: Grid");
	pShowVariablesLayout->insertWidget(2, pLayoutVariablesGrid);
	pVariableSettingsLayout->insertWidget(0, pShowVariables);
	
	QPushButton* pAcceptButton = new QPushButton;
	QPushButton* pCloseButton = new QPushButton;
	QBoxLayout* pButtonLayout = new QHBoxLayout;
	pAcceptButton->setText("Accept");
	connect(pAcceptButton, SIGNAL(clicked(bool)), this, SLOT(Accept()));
	pCloseButton->setText("Close");
	connect(pCloseButton, SIGNAL(clicked(bool)), this, SLOT(close()));
	pButtonLayout->insertWidget(0, pAcceptButton, 1);
	pButtonLayout->insertWidget(1, pCloseButton, 1);

	QBoxLayout* pMainLayout = new QVBoxLayout;
	pMainLayout->setSizeConstraint(QLayout::SetFixedSize);
	setLayout(pMainLayout);
	pMainLayout->insertWidget(0, pExpressionSettings, 1);
	pMainLayout->insertWidget(1, pVariableSettings, 1);
	pMainLayout->insertLayout(2, pButtonLayout, 0);
}

GNumericalExpressionSettingsWidget::~GNumericalExpressionSettingsWidget()
{
	
}

void GNumericalExpressionSettingsWidget::Accept()
{
	m_NumericalExpression->m_ExpressionDisplay->ExpressionChanged( m_NumericalExpression->m_Expression.StringValue() );
	m_NumericalExpression->ReCalculate();
	close();
}