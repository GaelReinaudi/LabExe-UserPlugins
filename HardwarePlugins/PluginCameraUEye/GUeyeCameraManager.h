#ifndef GUEYECAMERAMANAGER_H
#define GUEYECAMERAMANAGER_H
#include "plugincameraueye_global.h"

#include "device.h"
#include "param.h"

#include "uEye/uEye.h"

// from the QuEyeSdiDemo that uEye sent me when I asked for the linux example code
class GUeyeCameraEventThread;
class GUeyeCamera;

/////////////////////////////////////////////////////////////////////
//! \brief The GUeyeCameraManager class represents a uEye camera manager.
/*!
It takes care of finding out what camera are present, initialize them and give them unique ID names.

\todo Implement the detection of camera plugged in and out. So that the cameras present on the system can 
be updated without the need of restarting the whole program.
*/
class PLUGINCAMERAUEYE_EXPORT GUeyeCameraManager : public GHardDevice
{
	Q_OBJECT

public:
	GUeyeCameraManager(QString uniqueIdentifierName, QObject *parent);
	~GUeyeCameraManager();

	//! Reimplemented from GDevice
	QList<GDevice*> SubDevices() const;

protected:
	//! Reimplemented from GDevice
	virtual void PopulateDeviceWidget(GDeviceWidget* theDeviceWidget);

protected slots:
	//! called when a uEye event was detected by the event loop (the one in eventthread.cpp)
	void InterpretUeyeEvent(int whichEvent);

private:
	//! creates a unique ID using the serial number from the camera
	QString CreateUniqueCameraIdentifier( QString model, QString serialCam ) const;
// 	//! Get the serial of the camera using a name made with CreateUniqueCameraIdentifier()
// 	qlonglong GetSerialFromCameraIdentifier( QString strUniqueID ) const;
	//! repopulates the camera list
	void RefreshCameraList();

	// helps resolving camera id conflicts by assigning a handle that opens the camera using the dev id
	void ResolveCameraIDs( QMap<GUeyeCamera*, ulong> &mapOfCamIds, QMap<GUeyeCamera*, ulong> &mapOfDevIds );
	//! the lists of camera. it is refreshed by RefreshCameraList()
	QList<GDevice*> m_Cameras;
	GUeyeCameraEventThread* m_pEvDevremove;
	GUeyeCameraEventThread* m_pEvDevnew;

private:
	
};

#endif // GUEYECAMERAMANAGER_H
