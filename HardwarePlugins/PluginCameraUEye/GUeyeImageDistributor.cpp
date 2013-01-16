#include "GUeyeImageDistributor.h"
#include "GUeyeCamera.h"

GUeyeImageDistributor::GUeyeImageDistributor(GUeyeCamera *parent)
	: GImageProcessor(parent)
	, m_ThreadWaitForImages(false)
{
	// this is an image provider
	m_IsImageProvider = true;

	m_pParentUeyeCamera = parent;
	if(!m_pParentUeyeCamera)
		qWarning() << "The GUeyeCamera object pointer is 0! 9504447";
	else
		connect(this, SIGNAL(AoiChanged(QRect)), m_pParentUeyeCamera, SLOT(ChangeSensorAOI(QRect)), Qt::QueuedConnection);
}

GUeyeImageDistributor::~GUeyeImageDistributor()
{
	m_ThreadWaitForImages = false;
	if(!wait(2000))
		quit();
}

void GUeyeImageDistributor::run()
{	
	int nRet = 0;
	HIDS hCam = m_pParentUeyeCamera->m_CamHandle;
	if(hCam == 0) {
// 		qWarning() << "The Camera handle given to the GUeyeImageDistributor thread is 0! 413954";
		return;
	}
	if(!m_pParentUeyeCamera->IsAble())
		return;
	
	msleep(10);
	m_pParentUeyeCamera->ClearBufferQueue();
	nRet = m_pParentUeyeCamera->PrepareBufferQueue();

	nRet = is_CaptureVideo(hCam, IS_DONT_WAIT);

	char *pPix = 0;
	int nMemID = 0;
	m_ThreadWaitForImages = true;
	while(m_ThreadWaitForImages && m_pParentUeyeCamera->m_CamHandle){
		try {
			int transfetRet = is_WaitForNextImage(hCam, 500, &pPix, &nMemID);
			if(transfetRet == IS_SUCCESS) {
				BufferToTreat(pPix);
				is_UnlockSeqBuf (hCam, nMemID, pPix);
			}
			else if(transfetRet == IS_TRANSFER_FAILED) {
				UEYE_CAPTURE_STATUS_INFO CaptureStatusInfo;
				is_CaptureStatus (hCam, IS_CAPTURE_STATUS_INFO_CMD_GET,
					(void*)&CaptureStatusInfo,
					sizeof(CaptureStatusInfo));
				ulong caperr = CaptureStatusInfo.adwCapStatusCnt_Detail[IS_CAP_STATUS_API_CONVERSION_FAILED];
//				qDebug() << "Transfert failed" << caperr;
				BufferToTreat(0);
				emit ProcessorFailed();
			}
			else if(transfetRet == IS_TIMED_OUT) {
//				qDebug() << "WaitForNextImage timed-out.";
			}
			if(m_pParentUeyeCamera->m_WaitForOnlyOneImage) {
				m_pParentUeyeCamera->m_WaitForOnlyOneImage = false;
				break;
			}
		}
		catch(...) {
			break;
		}
	}

	is_StopLiveVideo(hCam, IS_DONT_WAIT);

	is_ExitImageQueue(hCam);
	is_ClearSequence(hCam);
}

void GUeyeImageDistributor::BufferToTreat( char * pPix)
{
	if(!pPix)
		return;
	HIDS hCam = m_pParentUeyeCamera->m_CamHandle;
	QRect aoi = m_pParentUeyeCamera->SensorAOI();
	int widht = aoi.width();
	int height = aoi.height();
	int bitsPPixel = m_pParentUeyeCamera->BitsPerPixel();
	int bytePerLine = 0;
	// the line pitch for making the QImage out of raw data
	is_GetImageMemPitch (hCam, &bytePerLine);
	// making a QImage
	QImage image((uchar*)(pPix), widht, height, bytePerLine, QImage::Format_Indexed8);
	// make a copy that will be free its memory once every reference to it will be deleted.
	QImage imageToSend = image.copy();
	GImageDouble imageDoubleToSend(imageToSend);
	// emitting the signal
// 	emit OutputImage(imageToSend);
	emit OutputImageDouble(imageDoubleToSend);
	// updates the frame-rate
	m_pParentUeyeCamera->ImagePerSecond();
}