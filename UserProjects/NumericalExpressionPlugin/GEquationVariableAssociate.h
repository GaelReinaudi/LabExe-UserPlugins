#ifndef GEQUATIONVARIABLEASSOCIATE_H
#define GEQUATIONVARIABLEASSOCIATE_H

#include "ToolBox/GInteractiveObject.h"
#include "Param/GParamString.h"

class GEquationVariableAssociate : public GInteractiveObject
{
	Q_OBJECT

public:
	GEquationVariableAssociate(QObject *parent);
	~GEquationVariableAssociate();

	//! Re-implemented
	virtual QWidget* ProvideNewWidget(QWidget* inWhichWidget);
	//! Re-implemented
	virtual QGraphicsItem* ProvideNewGraphicsItem(QGraphicsItem* pParentItem) {return 0;}
	//! Returns the name of the variable that the equation will use to represent the parameter
	QString VariableName() const { return m_VariableName.StringValue(); } 

public:
	//! Re-implemented
	void PopulateSettings( QSettings& inQsettings );
	//! Re-implemented
	void ReadFromSettings( QSettings& fromQsettings );

protected slots:
	//! Sets the name of the Variable
	void SetVariableName(QString varName);

signals:
	//! Emitted when the name of the variable changed
	void VariableNameChanged(QString varName);

private:
	GParamString m_VariableName;
};

#endif // GEQUATIONVARIABLEASSOCIATE_H
