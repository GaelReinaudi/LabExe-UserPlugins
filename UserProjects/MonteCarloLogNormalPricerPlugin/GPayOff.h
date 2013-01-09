#ifndef GPAYOFF_H
#define GPAYOFF_H

#include <QObject>

class GPayOff : public QObject
{
public:
	GPayOff(QObject *parent);
	virtual ~GPayOff();

	//! function that makes the PayOff a Functor.
	virtual double operator()(double theSpot) const = 0;

private:
	
};

#endif // GPAYOFF_H
