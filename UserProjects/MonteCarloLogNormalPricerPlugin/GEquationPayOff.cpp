#include "GEquationPayOff.h"

GEquationPayOff::GEquationPayOff(QObject *parent)
	: GPayOff(parent)
	, m_pEngine(0)
{
	m_pEngine = new GMathScriptEngine(this);
	m_ScriptSpot = m_pEngine->newVariant(0);
	m_pEngine->globalObject().setProperty("S", m_ScriptSpot);
	m_pEngine->SetProgram("100*(H(S - 100.0) - H(S - 120.0))");
}

GEquationPayOff::GEquationPayOff( const GParamString & ProgramString, QObject *parent )
	: GPayOff(parent)
	, m_pEngine(0)
{
	m_pEngine = new GMathScriptEngine(this);
	m_pEngine->globalObject().setProperty("S", m_ScriptSpot);
	m_pEngine->SetProgram(ProgramString.StringValue());
	connect(&ProgramString, SIGNAL(ValueUpdated(QString)), m_pEngine, SLOT(SetProgram(QString)));
}

GEquationPayOff::~GEquationPayOff()
{

}

double GEquationPayOff::operator()( double theSpot ) const
{
	m_ScriptSpot = m_pEngine->newVariant(theSpot);
	m_pEngine->globalObject().setProperty("S", m_ScriptSpot);
	return m_pEngine->Evaluate();
}