#include "GUeyeCameraManager.h"
#include "GUeyeCamera.h"
#include "eventthread.h"

G_REGISTER_HARD_DEVICE_CLASS(GUeyeCameraManager)

GUeyeCameraManager::GUeyeCameraManager(QString uniqueIdentifierName, QObject *parent)
	: GHardDevice(uniqueIdentifierName, parent)
{
	RefreshCameraList();

	// to monitor the camera connections and disconnections
	m_pEvDevremove = new GUeyeCameraEventThread();
	m_pEvDevnew = new GUeyeCameraEventThread();
	m_pEvDevremove->start (0, IS_SET_EVENT_REMOVAL);
	m_pEvDevnew->start (0, IS_SET_EVENT_NEW_DEVICE);
	connect(m_pEvDevnew, SIGNAL(eventhappen(int)), this, SLOT(InterpretUeyeEvent(int)));
	connect(m_pEvDevremove, SIGNAL(eventhappen(int)), this, SLOT(InterpretUeyeEvent(int)));
}

GUeyeCameraManager::~GUeyeCameraManager()
{
}

void GUeyeCameraManager::RefreshCameraList()
{	
	QSet<GDevice*> camRemoved;
	QSet<GDevice*> camConnected;
	QSet<GDevice*> oldCams = m_Cameras.toSet();
	
	m_Cameras.clear();

	// GAEL : code from the very good uEye programming manual : file:///C:/Program%20Files/IDS/uEye/Help/uEye_Manual/index.html
	// GAEL : code sample of function is_GetCameraList() : file:///C:/Program%20Files/IDS/uEye/Help/uEye_Manual/is_getcameralist.html

//	// enable the dialog based error report
//	is_SetErrorReport(0, IS_ENABLE_ERR_REP); //or IS_DISABLE_ERR_REP;

	// At least one camera must be available
	int nNumCam;
	if( is_GetNumberOfCameras( &nNumCam ) == IS_SUCCESS)
	{
		if( nNumCam >= 1 )
		{
			// Create new list with suitable size
			UEYE_CAMERA_LIST* pucl;
			pucl = (UEYE_CAMERA_LIST*) new char [sizeof (DWORD) + nNumCam * sizeof (UEYE_CAMERA_INFO)];
			pucl->dwCount = nNumCam;

			//Retrieve camera info
			if (is_GetCameraList(pucl) == IS_SUCCESS) {
				int iCamera;
				// a list to keep track of the cam ids. That will help us decide if we need to assign a new id.
				QMap<GUeyeCamera*, ulong> mapOfCamIds;
				QMap<GUeyeCamera*, ulong> mapOfDevIds;
				for (iCamera = 0; iCamera < (int)pucl->dwCount; iCamera++) {
					// creates the cameras object (GDevice)
					QString strModelCamera(pucl->uci[iCamera].Model);
					QString strSerialCamera(pucl->uci[iCamera].SerNo);
					ulong CameraID(pucl->uci[iCamera].dwCameraID);
					ulong DeviceID(pucl->uci[iCamera].dwDeviceID);
					qlonglong serialCamera = strSerialCamera.toLongLong();
					QString nameCamera = CreateUniqueCameraIdentifier(strModelCamera, strSerialCamera);
					qDebug() << "Camera" << nameCamera 
						<< "uEyeCameraID" << CameraID
						<< "uEyeDeviceID" << DeviceID
						;
					// if it already exist, lets not make it again.
					GUeyeCamera* pCamera = qobject_cast<GUeyeCamera*>(GetDeviceFromDeviceManager(nameCamera));
					// but let's make sure or set the correct parent module (in case it was created	at startup, without the module parent created...)
					if(pCamera && !pCamera->parent())
						pCamera->setParent(this);
					if(!pCamera)
						pCamera = new GUeyeCamera(nameCamera, this);

					mapOfCamIds.insert(pCamera, CameraID);
					mapOfDevIds.insert(pCamera, DeviceID);
					pCamera->m_CamHandle = (HIDS)(CameraID);

					m_Cameras.append(pCamera);
					disconnect(this, SIGNAL(IsAblenessMayHaveChanged(bool)), pCamera, SIGNAL(IsAblenessMayHaveChanged(bool)));
					connect(this, SIGNAL(IsAblenessMayHaveChanged(bool)), pCamera, SIGNAL(IsAblenessMayHaveChanged(bool)));
				}
				ResolveCameraIDs(mapOfCamIds, mapOfDevIds);
			}
		}
	}
	// what was added
	camConnected = m_Cameras.toSet().subtract(oldCams);
	// what was removed
	camRemoved = oldCams.subtract(m_Cameras.toSet());
	// appropriate thing to do
	foreach(GDevice* pDev, camRemoved) {
		GUeyeCamera* pCam = qobject_cast<GUeyeCamera*>(pDev);
		if(!pCam)
			continue;
		emit pCam->IsAblenessMayHaveChanged(false);
		pCam->CloseCamera();
	}
	// first we open the camera that had a unique camera ID
	foreach(GDevice* pDev, camConnected) {
		GUeyeCamera* pCam = qobject_cast<GUeyeCamera*>(pDev);
		if(!pCam)
			continue;
		if(pCam->m_IsUsingDeviceIdToOpen)
			continue;
		emit pCam->IsAblenessMayHaveChanged(true);
		pCam->LatterInitialization();
	}
	// then we open the one that had their handle changed by ResolveCameraIDs() to a value = (deviceID | IS_USE_DEVICE_ID)
	foreach(GDevice* pDev, camConnected) {
		GUeyeCamera* pCam = qobject_cast<GUeyeCamera*>(pDev);
		if(!pCam)
			continue;
		if(pCam->m_IsUsingDeviceIdToOpen) {
			emit pCam->IsAblenessMayHaveChanged(true);
			pCam->LatterInitialization();
		}
	}
}

void GUeyeCameraManager::ResolveCameraIDs(QMap<GUeyeCamera*, ulong> &mapOfCamIds, QMap<GUeyeCamera*, ulong> &mapOfDevIds)
{
	// if there are duplicate ids, we set the handle to open the device using the device id
	foreach(ulong cid, mapOfCamIds.values().toSet().toList()) {
		if(mapOfCamIds.keys(cid).count() > 1)
			foreach(GUeyeCamera* pCam, mapOfCamIds.keys(cid)) {
				pCam->m_CamHandle = (HIDS)(mapOfDevIds.value(pCam) | IS_USE_DEVICE_ID);
				pCam->m_IsUsingDeviceIdToOpen = true;
		}
	}
}

void GUeyeCameraManager::PopulateDeviceWidget(GDeviceWidget* theDeviceWidget )
{
}

QString GUeyeCameraManager::CreateUniqueCameraIdentifier( QString model, QString serialCam ) const
{
	return model + QString("-%1").arg(serialCam);
}

QList<GDevice*> GUeyeCameraManager::SubDevices() const
{
	return m_Cameras;
}

void GUeyeCameraManager::InterpretUeyeEvent( int whichEvent )
{
	if(whichEvent == IS_SET_EVENT_REMOVAL)
		RefreshCameraList();
	if(whichEvent == IS_SET_EVENT_NEW_DEVICE) {
		RefreshCameraList();
	}
}
