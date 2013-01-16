#ifndef GNUMERICALEXPRESSION_H
#define GNUMERICALEXPRESSION_H

#include "Param/GSingleParamBucket.h"
#include "Param/GParamBool.h"
#include "Param/GParamString.h"
#include "Script/GMathScriptEngine.h"

#include "Param/GParamBucket.h"
#include "GExpressionDisplay.h"
#include "GNumericalExpressionSettingsWidget.h"
#include "device.h"

class GNumericalExpression : public GProgDevice
{
	Q_OBJECT

public:
	GNumericalExpression(QObject *parent, QString uniqueIdentifierName);
	~GNumericalExpression();

public slots:
	//! Makes the expression to be evaluated and returned in the result param bucket.
	void ReCalculate(int debugInfo = -1);

protected:
	//! Re-implemented.
	void PopulateDeviceWidget(GDeviceWidget* theDeviceWidget);

private slots:
	//! called by the variable bucket so that we update the engine
	void AddVariableFromParam(GParam* forThatParam);
	//! called by the variable bucket so that we update the engine
	void RemoveVariableFromParam(int oldIndex, GParam* forThatParam);

private:
	GSingleParamBucket m_ValueBucket;
	GParamBucket m_VariableBucket;
	GParamBool m_EnableEvaluation;
	GParamString m_Expression;
	GExpressionDisplay* m_ExpressionDisplay;
	GMathScriptEngine* m_pScriptEngine;
	QScriptEngineDebugger* m_pEngineDebugger;

	friend class GNumericalExpressionSettingsWidget;
};

#endif // GNUMERICALEXPRESSION_H
