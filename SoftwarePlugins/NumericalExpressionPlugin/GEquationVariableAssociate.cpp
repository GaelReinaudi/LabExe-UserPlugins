#include "GEquationVariableAssociate.h"

GEquationVariableAssociate::GEquationVariableAssociate(QObject *parent)
	: GInteractiveObject(parent)
	, m_VariableName("", this)
{
}

GEquationVariableAssociate::~GEquationVariableAssociate()
{

}

QWidget* GEquationVariableAssociate::ProvideNewWidget( QWidget* inWhichWidget )
{
	QLineEdit* pNameEdit = m_VariableName.ProvideNewParamLineEdit(inWhichWidget);
	connect(pNameEdit, SIGNAL(textChanged(QString)), this, SLOT(SetVariableName(QString)));
	connect(&m_VariableName, SIGNAL(ValueUpdated(QString)), this, SIGNAL(VariableNameChanged(QString)));
	return pNameEdit;
}

void GEquationVariableAssociate::SetVariableName( QString varName )
{
	m_VariableName = varName;
}

void GEquationVariableAssociate::PopulateSettings( QSettings& inQsettings )
{
	inQsettings.setValue("Variable-name", VariableName());
}

void GEquationVariableAssociate::ReadFromSettings( QSettings& fromQsettings )
{
	QString varName = fromQsettings.value("Variable-name").toString();
	m_VariableName = varName;
}