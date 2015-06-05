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
	int bytePPixel = bytePerLine/widht;//added 2015-06-02; double checked. For 8-bit should be 1, for 12-bit should be 2. 
	//qDebug()<<"Bart:(byteperline,width,height,byteperpixel):"<<bytePerLine<<" "<<widht<<" "<<height<<" "<<bytePPixel;
	//qDebug()<<"Bart: bitsPPixel = "<<bitsPPixel;

	//2015-06-02: Here is Gael's original code that took the camera data and turned it into an 8-bit QImage, losing any higher bit depth information: 
/*	// making a QImage
	QImage image((uchar*)(pPix), widht, height, bytePerLine, QImage::Format_Indexed8);
	// make a copy that will be free its memory once every reference to it will be deleted.
	QImage imageToSend = image.copy();
	GImageDouble imageDoubleToSend(imageToSend);
	// emitting the signal
// 	emit OutputImage(imageToSend);
	emit OutputImageDouble(imageDoubleToSend);
	// updates the frame-rate
	m_pParentUeyeCamera->ImagePerSecond();
*/

	//2015-06-02: New code to process camera data without reducing to 8-bits: 
	//Don't use this://GImageDouble imageDoubleToSend((char*)pPix,widht,height,bytePerLine,bitsPPixel);//tried making new constructor to do this, but breaks b/c cannot pass pPix correctly. 
	GImageDouble imageDoubleToSend(widht,height);//Create empty GImageDouble of right size.
	double* doubleArrayToFill = imageDoubleToSend.DoubleArray().data();//Get access to its DoubleArray.
	ushort tempdest;
	//Fill DoubleArray directly with camera data: 
	if(bytePPixel==1){
		for(int iTot=0; iTot < widht*height;iTot++){
			//1 byte per pixel is expected for 8-bit image depths.
			doubleArrayToFill[iTot] = uchar(pPix[iTot]);//works for 8-bit, but not for 12-bit. Seems linear with input light.  
		}
	}
	else if(bytePPixel==2){
		//2 byte per pixel is expected for 12-bit image depths.
		for(int iTot=0; iTot < widht*height;iTot++){
			memcpy(&tempdest,&pPix[2*iTot],sizeof(ushort));
			doubleArrayToFill[iTot] = tempdest;
			//This works for 12-bit, but not for 8-bit.  Seems linear with input light. 
		}
	}
	else{
		//Don't know what to do so complain to user! 
		qDebug()<<"GUEyeImageDistributor:BufferToTreat() doesn't know what to do with camera image because > 2 bytes per pixel!!!!!";
	}
	//Now create QImage: 
	imageDoubleToSend.FillQimageFromUsingDoubleArray(0,qPow(2,bitsPPixel)-1);//Tell GImageDouble to create 8-bit image from DoubleArray, which could come from a higher bit depth image. 
	//imageDoubleToSend.FillQimageFromUsingDoubleArrayAndBitDepth(bitsPPixel);//(Experimental) Tell GImageDouble to create 8-bit image from DoubleArray, which could come from a higher bit depth image.
	//Now you've successfully prepared imageDoubleToSend with full data in DoubleArray and approximate image in QImage.  Congrats you! 
	
	//qDebug()<<"Pixel(100,100) value: "<<imageDoubleToSend.PixelAt(100,100);

	emit OutputImageDouble(imageDoubleToSend);//Emit signal: sends out the image to be used! 
	m_pParentUeyeCamera->ImagePerSecond();//update the frame rate. 
}