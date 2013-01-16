#include "GNumericalExpression.h"

GNumericalExpression::GNumericalExpression(QObject *parent, QString uniqueIdentifierName)
	: GProgDevice(parent, uniqueIdentifierName)
	, m_ValueBucket("Result", this)
	, m_VariableBucket("Variables", this)
	, m_EnableEvaluation("EnableEvaluation", this)
	, m_Expression("Expression", this)
{
	// Expression Display Initialization
	m_ExpressionDisplay = new GExpressionDisplay(this);

	// Script Engine Initialization
	m_pScriptEngine = new GMathScriptEngine(this);
// 	m_ScriptEngineDebugger = new QScriptEngineDebugger;

	m_VariableBucket.AddExtraFieldString("symb");


	connect(&m_Expression, SIGNAL(ValueUpdated(QString)), m_pScriptEngine, SLOT(SetProgram(QString)));
	connect(&m_Expression, SIGNAL(ValueUpdated(QString)), m_pScriptEngine, SLOT(Evaluate()));
	connect(&m_VariableBucket, SIGNAL(BucketUpdatedValues(int)), this, SLOT(ReCalculate(int)));
	connect(m_pScriptEngine, SIGNAL(Evaluated(double)), &m_ValueBucket, SLOT(SetParamValue(double)));

	connect(&m_VariableBucket, SIGNAL(ParamAdded(GParam*)), this, SLOT(AddVariableFromParam(GParam*)), Qt::QueuedConnection);
	connect(&m_VariableBucket, SIGNAL(ParamRemoved(int, GParam*)), this, SLOT(RemoveVariableFromParam(int, GParam*)));
}

GNumericalExpression::~GNumericalExpression()
{

}

void GNumericalExpression::ReCalculate(int debugInfo /*= -1*/)
{
	// Evaluate and display the result.
	QScriptValue scriptResult = m_pScriptEngine->Evaluate();
}

void GNumericalExpression::PopulateDeviceWidget(GDeviceWidget* theDeviceWidget)
{
	QBoxLayout* pDeviceLayout = new QVBoxLayout();
	theDeviceWidget->AddSubLayout(pDeviceLayout);
	pDeviceLayout->setContentsMargins(1, 1, 1, 1);
	pDeviceLayout->setSpacing(1);

	QBoxLayout* pVariablesAndValueLayout = new QHBoxLayout();
	QBoxLayout* pExpressionLayout = new QVBoxLayout();
	pExpressionLayout->addWidget(m_Expression.ProvideNewParamLineEdit(theDeviceWidget));
	pExpressionLayout->addWidget(m_Expression.ProvideNewLabel(theDeviceWidget));

	pVariablesAndValueLayout->addWidget(m_VariableBucket.ProvideNewParamWidget(theDeviceWidget));
	pVariablesAndValueLayout->addWidget(m_ValueBucket.ProvideNewParamWidget(theDeviceWidget));

//	QPushButton* pSettingsButton = new QPushButton("Settings");
//	GNumericalExpressionSettingsWidget* pSettingsWindow = new GNumericalExpressionSettingsWidget(this);
//	connect(pSettingsButton, SIGNAL(clicked(bool)), pSettingsWindow, SLOT(show()));
//	pVariablesAndValueLayout->insertWidget(1, pSettingsButton);

	pDeviceLayout->addLayout(pExpressionLayout);
	pDeviceLayout->addLayout(pVariablesAndValueLayout);

	pDeviceLayout->addStretch();
}

void GNumericalExpression::AddVariableFromParam( GParam* forThatParam )
{
	GParamString* pNameStr = m_VariableBucket.ExtraParamString(forThatParam, "symb");
	GParamNum* pParNum = qobject_cast<GParamNum*>(forThatParam);
	if(!pNameStr || !pParNum) {
		qDebug() << "problem AddVariableFromParam()";
		return;
	}
	m_pScriptEngine->RegisterVariable(pNameStr, pParNum);
}

void GNumericalExpression::RemoveVariableFromParam(int oldIndex, GParam* forThatParam)
{
	GParamString* pNameStr = m_VariableBucket.ExtraParamString(forThatParam, "symb");
	GParamNum* pParNum = qobject_cast<GParamNum*>(forThatParam);
	if(!pNameStr || !pParNum) {
		qWarning() << "problem RemoveVariableFromParam()";
		return;
	}
	m_pScriptEngine->RemoveVariable(pNameStr, pParNum);
}






