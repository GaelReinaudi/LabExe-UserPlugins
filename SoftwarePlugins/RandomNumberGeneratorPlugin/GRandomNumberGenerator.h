#ifndef GRandomNumberGenerator_H
#define GRandomNumberGenerator_H

#include "device.h"
#include "param.h"

class QTimer;

/////////////////////////////////////////////////////////////////////
//! \brief The GRandomNumberGenerator class implements a GProgDevice.
/*!
This prog device allows you to ..............
*/
class GRandomNumberGenerator : public GProgDevice
{
	Q_OBJECT

public:
	GRandomNumberGenerator(QObject *parent, QString uniqueIdentifierName = "");

	~GRandomNumberGenerator();

public slots:
	//! Makes the generator to generate on the ticks of a timer
	void Activate(bool doGenerate);
	//! generates one random number
	double GenerateRandom();
	//! re set the seed value m_Seed
	void SetSeed();

protected:
	//! Re-implemented
	void PopulateDeviceWidget(GDeviceWidget* theDeviceWidget);

private:
	//! the seed of the random numbers
	GParamInt m_Seed;
	//! the upper value for a uniform distribution
	GParamDouble m_MaxUniformValue;
	//! the output of the generator
	GParamDouble m_LastOut;
	//! the state, generating or not
	GParamBool m_DoGenerate;
	//! the m_pTimer
	QTimer* m_pTimer;

};

#endif // GRandomNumberGenerator_H
