#ifndef GNUMERICALEXPRESSIONSETTINGS_H
#define GNUMERICALEXPRESSIONSETTINGS_H

#include <QWidget>
#include "ToolBox/GSerializable.h"

class GNumericalExpression;

class GNumericalExpressionSettingsWidget : public QWidget
{
	Q_OBJECT

public:
	GNumericalExpressionSettingsWidget(GNumericalExpression* numericalExpression, QObject* parent = NULL);
	~GNumericalExpressionSettingsWidget();

private slots:
	void Accept();

private:
	GNumericalExpression* m_NumericalExpression;
};

#endif // GNUMERICALEXPRESSIONSETTINGS_H