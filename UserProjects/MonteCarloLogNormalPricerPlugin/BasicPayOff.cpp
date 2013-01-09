#include "BasicPayOff.h"

GEuropeanCallPayOff::GEuropeanCallPayOff(double theStrike, QObject *parent /*= 0*/)
	: GPayOff(parent)
	, m_Strike(theStrike)
{

}

GEuropeanCallPayOff::~GEuropeanCallPayOff()
{

}

double GEuropeanCallPayOff::operator()( double theSpot ) const
{
	return qMax(0.0, theSpot - m_Strike);
}

GDigitalCallPayOff::GDigitalCallPayOff(double theStrike, QObject *parent /*= 0*/)
	: GPayOff(parent)
	, m_Strike(theStrike)
{

}

GDigitalCallPayOff::~GDigitalCallPayOff()
{

}

double GDigitalCallPayOff::operator()( double theSpot ) const
{
	return theSpot - m_Strike >= 0 ? 100.0 : 0.0;
}