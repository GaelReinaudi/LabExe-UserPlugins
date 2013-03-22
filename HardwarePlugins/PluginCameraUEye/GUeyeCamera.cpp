#include "GUeyeCamera.h"
#include "GUeyeCameraManager.h"
#include "GUeyeImageDistributor.h"

G_REGISTER_HARD_DEVICE_CLASS(GUeyeCamera)

GUeyeCamera::GUeyeCamera(QString uniqueIdentifierName, QObject *parent)
	: GCamera(uniqueIdentifierName, parent, 0 /*new GUeyeImageDistributor(this)*/)
	, m_CamHandle(0)
	, m_nColorMode(0)
	, m_nBitsPerPixel(0)
	, m_WaitForOnlyOneImage(false)
	, m_wasShootingAndShouldAutoRestart(false)
	, m_IsUsingDeviceIdToOpen(false)
	, m_PixelClock("Pix clock [MHz]", this)
{
 	m_pImageProcessor = new GUeyeImageDistributor(this);
	m_PixelClock.SetTypicalStep(1.0);
	m_PixelClock.SetDisplayDecimals(0);
}

GUeyeCamera::~GUeyeCamera()
{
	CloseCamera();
}

void GUeyeCamera::PopulateDeviceWidget(GDeviceWidget* theDeviceWidget )
{
	QFormLayout* pLay = new QFormLayout(theDeviceWidget);
	pLay->setSpacing(1);
	pLay->setContentsMargins(1, 1, 1, 1);
	pLay->addRow(m_PixelClock.ProvideNewLabel(theDeviceWidget), m_PixelClock.ProvideNewParamSpinBox(theDeviceWidget));
}

void GUeyeCamera::SetSystemDeviceID( ulong DeviceID )
{
	// The camera is opened using the device ID instead of the camera ID. For details on device ID please refer to the is_GetCameraList() chapter.
//	m_CamHandle = (HIDS)(DeviceID | IS_USE_DEVICE_ID);
	m_CamHandle = (HIDS)(DeviceID);
}

bool GUeyeCamera::IsAble() const
{
	bool bHandleUsedToOpenCamera = !(m_CamHandle & IS_USE_DEVICE_ID);
	bool bHandle = m_CamHandle != 0;
	return bHandleUsedToOpenCamera && bHandle;
}

bool GUeyeCamera::CloseCamera()
{
	if(!IsAble())
		return false;

	// bool to turn the acquisition back on when camera disconnected and reconnected
	m_wasShootingAndShouldAutoRestart = ImageProcessor()->isRunning();

	// stops the image processor so that it doesn't use a deallocated resource
	ImageProcessor()->StopProcessing();
	ImageProcessor()->wait();

	int nRet = is_ExitCamera(m_CamHandle);
	if (nRet != IS_SUCCESS) {
		qDebug() << "closing camera failed" << UniqueSystemID();
		return false;
	}
	return true;
}

bool GUeyeCamera::OpenCamera()
{
// 	if(!m_CamHandle)
// 		qWarning() << "The uEye camera device ID is 0. Check that the SetSystemDeviceID() was called before OpenCamera().";
	// The camera is opened using the device ID instead of the camera ID. For details on device ID please refer to the is_GetCameraList() chapter.

	bool wasShooting = m_wasShootingAndShouldAutoRestart;

	CloseCamera();

	// turn the shooting back on ?
	if(wasShooting)
		QTimer::singleShot(0, this, SLOT(ContinuousShot()));

//	m_CamHandle = (HIDS) (0 | IS_USE_DEVICE_ID);  
	int nRet = is_InitCamera(&m_CamHandle, NULL);
	if (nRet != IS_SUCCESS) {
//		qDebug() << "initialization failed" << UniqueSystemID();
		return false;
	}
	else
		qDebug() << "initialization successful" << UniqueSystemID();
	// let's set the camera ID to the m_CamHandle value: It may help the driver to recognize which handle represents which camera
	nRet = is_SetCameraID(m_CamHandle, m_CamHandle);

	// we will always want to use the DIB mode, not the Direct3D mode
	nRet = is_SetDisplayMode(m_CamHandle, IS_SET_DM_DIB);

	// get board info
	CAMINFO CameraInfo;
	is_GetCameraInfo( m_CamHandle, &CameraInfo );
	// get sensor info
	SENSORINFO SensorInfo;
	is_GetSensorInfo(m_CamHandle, &SensorInfo );

	if(SensorInfo.nColorMode == IS_COLORMODE_MONOCHROME) {
		// for monochrome camera models use Y8 mode
		m_nColorMode = IS_SET_CM_Y8;
		m_nBitsPerPixel = 8;
	}
	else {
		qWarning() << "This camera" << Name() << "is not Monochrome!";
		m_nColorMode = is_SetColorMode(m_CamHandle, IS_GET_COLOR_MODE);
	}

	qDebug() << "bits per pixels" << m_nBitsPerPixel;
	// init image size
	qDebug() << "Max image size" << GetMaxImageSize();
	// init expo range
//	qDebug() << "Exposure range" << GetExposureMin() << "to" << GetExposureMax();

	// pixel clock range
	unsigned int nRange[3];
	if(is_PixelClock(m_CamHandle, IS_PIXELCLOCK_CMD_GET_RANGE, (void*)nRange, sizeof(nRange)) == IS_SUCCESS) {
		unsigned int pClockMin = nRange[0];
		unsigned int pClockMax = nRange[1];
		unsigned int pClockInt = nRange[2];
		m_PixelClock.SetHardLimits(pClockMin, pClockMax);
		qDebug() << "Pixel clock range" << pClockMin << "to" << pClockMax;
	}

	SetPixelClock_MHz(m_PixelClock);
	connect(&m_PixelClock, SIGNAL(ValueUpdated(double)), this, SLOT(SetPixelClock_MHz()), Qt::UniqueConnection);

	if (nRet == IS_SUCCESS) {
		// set the desired color mode
		is_SetColorMode(m_CamHandle, m_nColorMode);
	}  

	// test
	int XPos = 541;
	int YPos = 1024/2-1024/8;
	int Width = 233;
	int Height = 1024/4;
// 	if(is_SetAOI (m_CamHandle, IS_SET_IMAGE_AOI, &XPos, &YPos, &Width, &Height) != IS_SUCCESS) 
	{
		Height = 4;
	}

	return true;
}

QSize GUeyeCamera::GetMaxImageSize() const
{
	// if it was already queried, we return it directly
	if(m_MaxImageSize != QSize())
		return m_MaxImageSize;
	//else we query it and store it in m_MaxImageSize

	// Check if the camera supports an arbitrary SensorAOI
	int nAOISupported = 0;
	bool bAOISupported = true;
	if(is_ImageFormat(m_CamHandle, IMGFRMT_CMD_GET_ARBITRARY_AOI_SUPPORTED, (void*)&nAOISupported, sizeof(nAOISupported)) == IS_SUCCESS) {
		bAOISupported = (nAOISupported != 0);
	}

// 	if(bAOISupported) {
		// Get maximum image size
		SENSORINFO sInfo;
		is_GetSensorInfo (m_CamHandle, &sInfo);
		m_MaxImageSize.rwidth() = sInfo.nMaxWidth;
// 		m_MaxImageSize.rheight() = sInfo.nMaxHeight;
// 	}
// 	else {
// 		// Get image size of the current format
// 		m_MaxImageSize.rwidth() = is_SetImageSize(m_CamHandle, IS_GET_IMAGE_SIZE_X, 0);
// 		m_MaxImageSize.rheight() = is_SetImageSize(m_CamHandle, IS_GET_IMAGE_SIZE_Y, 0);
// 	}
	return m_MaxImageSize;
}

double GUeyeCamera::SetExposureTime( double proposedNewExpo )
{
	// 0.0 would be a bad choice because the uEye camera will set 1/framerate
	proposedNewExpo = qMax(proposedNewExpo, 1e-9);
	double actualValueUsed = 0.0;
	is_Exposure(m_CamHandle, IS_EXPOSURE_CMD_SET_EXPOSURE, (void*)&proposedNewExpo, sizeof(proposedNewExpo));
	is_Exposure(m_CamHandle, IS_EXPOSURE_CMD_GET_EXPOSURE, (void*)&actualValueUsed, sizeof(actualValueUsed));
	qDebug() << "Exposure set to" << actualValueUsed << "ms";
	return actualValueUsed;
}

double GUeyeCamera::SetGainFactor( double proposedGainFactor )
{
	// get the max gain
	int maxGainPercent = is_SetHWGainFactor(m_CamHandle, IS_INQUIRE_MASTER_GAIN_FACTOR, 100);
	if(maxGainPercent <= 100)
		return -1.0;
	int proposedGainPercent = int(proposedGainFactor * 100.0);
	// the gain in percent in a valid range
	int gainPercent = qMin(qMax(proposedGainPercent, 100), maxGainPercent);
	// set it
	int actualGainPercentUsed = is_SetHWGainFactor(m_CamHandle, IS_SET_MASTER_GAIN_FACTOR, gainPercent);
	double actualGainUsed = double(actualGainPercentUsed) / 100.0;
	qDebug() << "Gain set to" << actualGainUsed;
	return actualGainUsed;
}

double GUeyeCamera::GetExposureMin()
{
// NO! because the range changes actually depending on the pixel clock and other stuff!
// 	// if the range looks valid, it means we did query it already
// 	if(m_ExpoRange.minValue() >= 0 && m_ExpoRange.maxValue() >= m_ExpoRange.minValue())
// 		return m_ExpoRange;
// 	// else, we do query it:

	double dblRange[3];
	double minExpo = 1e-9, maxExpo = 1e9, incExpo = 3.1415;
	if(IsAble()) {
		int nRet = is_Exposure(m_CamHandle, IS_EXPOSURE_CMD_GET_EXPOSURE_RANGE, (void*)&dblRange, sizeof(dblRange));
		minExpo = dblRange[0];
		maxExpo = dblRange[1];
		incExpo = dblRange[2];
	}
	return minExpo;
}

double GUeyeCamera::GetExposureMax()
{
	double dblRange[3];
	double minExpo = 1e-9, maxExpo = 1e9, incExpo = 3.1415;
	if(IsAble()) {
		int nRet = is_Exposure(m_CamHandle, IS_EXPOSURE_CMD_GET_EXPOSURE_RANGE, (void*)&dblRange, sizeof(dblRange));
		minExpo = dblRange[0];
		maxExpo = dblRange[1];
		incExpo = dblRange[2];
	}
	return maxExpo;
}

QRect GUeyeCamera::SensorAOI() const
{
	IS_RECT rectAOI;
	if(is_AOI(m_CamHandle, IS_AOI_IMAGE_GET_AOI, (void*)&rectAOI, sizeof(rectAOI)) == IS_SUCCESS) {
		QRect theAOI(rectAOI.s32X, rectAOI.s32Y, rectAOI.s32Width, rectAOI.s32Height);
		return theAOI;
	}
	return QRect();
}

void GUeyeCamera::SingleShotNow()
{
	if(!ImageProcessor())
		return;
	ContinuousShot(false);
	ImageProcessor()->wait();

	// tell to wait one picture,
	m_WaitForOnlyOneImage = true;
	// and take it
	ContinuousShot(true);
	is_ForceTrigger(m_CamHandle);
	// it should stop the acquisition after one image or failure, but just in case:
	ContinuousShot(false);
	ImageProcessor()->wait();
}

bool GUeyeCamera::SupportsExternalTrigger() const
{
	int ret = is_SetExternalTrigger(m_CamHandle, IS_GET_SUPPORTED_TRIGGER_MODE);
	bool isTrigableLoHi = (ret & IS_SET_TRIGGER_LO_HI);
	return isTrigableLoHi;
}

void GUeyeCamera::UseExternalTrigger( bool yesORno )
{
	int nTriggerMode = yesORno ? IS_SET_TRIGGER_LO_HI : IS_SET_TRIGGER_OFF;
	int ret = is_SetExternalTrigger (m_CamHandle, nTriggerMode);
//	qDebug() << "Use trigger set to" << nTriggerMode;
}

void GUeyeCamera::ContinuousShot(bool StartOrStop)
{
	if(!ImageProcessor())
		return;

	if(StartOrStop) {
		ImageProcessor()->start();
	}
	else {
		ImageProcessor()->StopProcessing();
		ImageProcessor()->wait();
		emit FrameRateChanged(0.0);
	}
}

double GUeyeCamera::ImagePerSecond()
{
	double fps = 0.0;
	is_GetFramesPerSecond(m_CamHandle, &fps);
	emit FrameRateChanged(fps);
	return fps;
}

int GUeyeCamera::PrepareBufferQueue()
{
	int nRet = 0;
	QRect aoi = SensorAOI();
	int widht = aoi.width();
	int height = aoi.height();
	int bitsPPixel = BitsPerPixel();
	// clears the sequence if any before filling it
	nRet = is_ClearSequence(m_CamHandle);
	for(int i = 0; i < G_UEYE_NUM_BUFFER_QUEUE; i++) {
		char *pPix = 0;
		int imID = 0;
		nRet += is_AllocImageMem(m_CamHandle, widht, height, bitsPPixel, &pPix, &imID);
		nRet += is_AddToSequence(m_CamHandle, pPix, imID);
		// keeps track of the buffers allocated for memory management purposes
		m_AllocatedBuffer.insert(pPix, imID);
	}
	nRet += is_InitImageQueue (m_CamHandle, 0);
	return nRet;
}

void GUeyeCamera::ClearBufferQueue()
{
// TO CONTINUE
// maybe keep a track of the mem buffere imID, seqIndex like in the QuEyeSdiDemo example where there is a struct UEYE_IMAGE.
// maybe have some mechainism to prevent celaning images that are still in use. The images could be copied or protected with some kind of mutex.
	foreach(char* ppix, m_AllocatedBuffer.keys()) {
		int imID = m_AllocatedBuffer.value(ppix);
		is_FreeImageMem(m_CamHandle, ppix, imID);
		m_AllocatedBuffer.remove(ppix);
	}
}

QRect GUeyeCamera::SetSensorAOI( QRect AoiRect )
{
	// the old sensor AOI
	QRect oldAOI = SensorAOI();
	if(AoiRect == oldAOI)
		return oldAOI;

	QSize minSizeAoi = QSize(32, 4);
	int gridStepX = 4;
	int gridStepY = 2;

	int halfGridStepX = gridStepX / 2;
	int halfGridStepY = gridStepY / 2;

	// makes the rect one pixel larger for the border right and bottom to match the grid
	AoiRect.adjust(0, 0, 1, 1);

	// snap the angles of the rectangle to gris points
	int usedLeft	= ((AoiRect.left()   + halfGridStepX) / gridStepX) * gridStepX;
	int usedRight	= ((AoiRect.right()  + halfGridStepX) / gridStepX) * gridStepX;
	int usedTop		= ((AoiRect.top()    + halfGridStepY) / gridStepY) * gridStepY;
	int usedBottom	= ((AoiRect.bottom() + halfGridStepY) / gridStepY) * gridStepY;
	usedRight--;
	usedBottom--;

	QRect usedRect = QRect(QPoint(usedLeft, usedTop), QPoint(usedRight, usedBottom));
	// if it is still to small we expand it by grid step size on each direction
	int diffWidth = minSizeAoi.width() - usedRect.width();
	if(diffWidth > 0) {
		int diffStepX = diffWidth / 2;
		usedRect.adjust(-diffStepX, 0, diffStepX, 0);
	}
	int diffHeight = minSizeAoi.height() - usedRect.height();
	if(diffHeight > 0) {
		int diffStepY = diffHeight / 2;
		usedRect.adjust(0, -diffStepY, 0, diffStepY);
	}

	// Sets the position and size of the image by using an object of the IS_RECT type.
	IS_RECT rectAOI;
	rectAOI.s32X = usedRect.left();
	rectAOI.s32Y = usedRect.top();
	rectAOI.s32Width = usedRect.width();
	rectAOI.s32Height = usedRect.height();

	// was the camera running
	bool wasRunning = ImageProcessor()->isRunning();
	ContinuousShot(false);

	if(is_AOI(m_CamHandle, IS_AOI_IMAGE_SET_AOI, (void*)&rectAOI, sizeof(rectAOI)) != IS_SUCCESS)
		qWarning() << "GUeyeCamera::SetSensorAOI" << "Could not set the AOI to the rectangle" << usedRect;

	if(wasRunning) {
		ContinuousShot(true);
	}
	QRect reallyUsedRect = SensorAOI();
	return reallyUsedRect;
}

int GUeyeCamera::SetPixelClock_MHz( int proposedPixelClock /*= 0*/)
{
	// default to m_PixelClock if no argument is passed
	if(proposedPixelClock == 0)
		proposedPixelClock = m_PixelClock;

	int nRet = is_PixelClock(m_CamHandle, IS_PIXELCLOCK_CMD_SET, (void*)&proposedPixelClock, sizeof(proposedPixelClock));
	int currentPixelClock = 0;
	is_PixelClock(m_CamHandle, IS_PIXELCLOCK_CMD_GET, (void*)&currentPixelClock, sizeof(currentPixelClock));
 	int defaultPixelClock = 0;
	is_PixelClock(m_CamHandle, IS_PIXELCLOCK_CMD_GET_DEFAULT, (void*)&defaultPixelClock, sizeof(defaultPixelClock));
	if(nRet != IS_SUCCESS) {
		if(IsAble())
			qDebug() << "Could not set the pixel clock value [MHz]:" << proposedPixelClock << ". Using instead:" << currentPixelClock;
	}
	else
		UpdateExposureTime();

	qDebug() << "Pixel clock:" << currentPixelClock;
	qDebug() << "Exposure range:" << GetExposureMin() << "to" << GetExposureMax();

	return currentPixelClock;
}
