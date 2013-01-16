#ifndef BASICPAYOFF_H
#define BASICPAYOFF_H

#include "GPayOff.h"

class GEuropeanCallPayOff : public GPayOff
{
	// 	Q_OBJECT

public:
	GEuropeanCallPayOff(double theStrike, QObject *parent = 0);
	~GEuropeanCallPayOff();

	//! Re-implemented
	double operator()(double theSpot) const;

private:
	double m_Strike;

};

class GDigitalCallPayOff : public GPayOff
{
	// 	Q_OBJECT

public:
	GDigitalCallPayOff(double theStrike, QObject *parent = 0);
	~GDigitalCallPayOff();

	//! Re-implemented
	double operator()(double theSpot) const;

private:
	double m_Strike;

};

#endif // BASICPAYOFF_H
