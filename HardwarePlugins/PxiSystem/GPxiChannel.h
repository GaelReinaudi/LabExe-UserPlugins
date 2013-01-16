#ifndef GPXICHANNEL_H
#define GPXICHANNEL_H

#include "device.h"
#include "param.h"
class GDAQmxModule;

/////////////////////////////////////////////////////////////////////
//! \brief The G
/*!
more
*/
class GPxiChannel : public GHardDevice
{
public:
	GPxiChannel(QString uniqueIdentifierName, QObject* parentDevice);
	~GPxiChannel();

	//! returns the parent GDAQmxModule if there is one
	GDAQmxModule* ParentModule() const;

protected:
	//! Reimplemented from GDevice. Provides a shorter name for the PXI channel.
	virtual QString DefaultShortName() const;

private:
	
};

#endif // GPXICHANNEL_H
