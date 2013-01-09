#ifndef GEQUATIONPAYOFF_H
#define GEQUATIONPAYOFF_H

#include "GPayOff.h"
#include "Script/GMathScriptEngine.h"

class GEquationPayOff : public GPayOff
{
	Q_OBJECT

public:
	GEquationPayOff(QObject *parent);
	//! Constructor that sets the program to evaluate and connect any change to the string so that the program is up to date
	GEquationPayOff(const GParamString & ProgramString, QObject *parent);
	~GEquationPayOff();

	//! Re-implemented
	double operator()(double theSpot) const;

private:
	//! Engine for evaluating the expression
	GMathScriptEngine* m_pEngine;
	//! ScriptValue that represents the spot
	mutable QScriptValue m_ScriptSpot;
};

#endif // GEQUATIONPAYOFF_H
