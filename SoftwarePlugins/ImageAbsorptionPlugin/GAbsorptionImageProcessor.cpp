#include "GAbsorptionImageProcessor.h"

GAbsorptionImageProcessor::GAbsorptionImageProcessor(QObject *parent, QString uniqueIdentifierName /*= ""*/)
	: GImageProcessor(parent, uniqueIdentifierName)
	, m_BatchTimeOut_ms(500)
	, m_CurrentImageType(Suspicious)
	, m_DisplayRailDown("Disp-min", this)
	, m_DisplayRailUp("Disp-max", this)
{
	// this is an image provider
	m_IsImageProvider = true;
	m_DisplayRailUp = 1.0;

	m_DisplayRailDown.SetHardLimits(-99.9, 999.9);
	m_DisplayRailUp.SetHardLimits(-99.9, 999.9);
}

GAbsorptionImageProcessor::~GAbsorptionImageProcessor()
{
	//TryThread
	wait(2000);
	terminate();
	m_ImageIn.clear();
}

void GAbsorptionImageProcessor::PopulateDeviceWidget(GDeviceWidget* theDeviceWidget )
{
	QLabel* downLabel = m_DisplayRailDown.ProvideNewLabel(theDeviceWidget);
	GDoubleSpinBox* pDown = m_DisplayRailDown.ProvideNewParamSpinBox(theDeviceWidget); 
	QLabel* upLabel = m_DisplayRailUp.ProvideNewLabel(theDeviceWidget);
	GDoubleSpinBox* pUp = m_DisplayRailUp.ProvideNewParamSpinBox(theDeviceWidget); 
	// A layout, in which we place the label and the spinbox 
	QFormLayout* downLayout = new QFormLayout();
	downLayout->addRow(downLabel, pDown);
	QFormLayout* upLayout = new QFormLayout();
	upLayout->addRow(upLabel, pUp);
	QHBoxLayout* hLayout = new QHBoxLayout();
	hLayout->addItem(downLayout);
	hLayout->addItem(upLayout);
	theDeviceWidget->AddSubLayout(hLayout);
}

void GAbsorptionImageProcessor::PopulateSettings( QSettings& inQsettings )
{
	GImageProcessor::PopulateSettings(inQsettings);
	inQsettings.setValue("dispMin", (double)m_DisplayRailDown);
	inQsettings.setValue("dispMax", (double)m_DisplayRailUp);
}

void GAbsorptionImageProcessor::InterpretSettings( QSettings& fromQsettings )
{
	GImageProcessor::InterpretSettings(fromQsettings);
	m_DisplayRailDown = fromQsettings.value("dispMin", 0.0).toDouble();
	m_DisplayRailUp = fromQsettings.value("dispMax", 5.0).toDouble();
}

void GAbsorptionImageProcessor::ProcessImageAOIed(const GImageDouble & aoiImage)
{
	m_ImageMutex.lock();
	QDateTime timeThisPicture = aoiImage.DateTimeCreated();
	ImageType whichImageType = WichImageMustThatBe(timeThisPicture);
	switch(whichImageType) {
	case Atom:
		m_ImageIn.clear();
		m_ImageIn.insert(whichImageType, aoiImage);
// 		qDebug() << "Atom image received. time stamp" << timeThisPicture << "ms = " << timeThisPicture.toMSecsSinceEpoch() << "Previous" << m_LastReceivedPictureCreationDate.toMSecsSinceEpoch() << "ms since last = " << m_LastReceivedPictureCreationDate.time().msecsTo(timeThisPicture.time());
		break;
	case Beam:
		m_ImageIn.insert(whichImageType, aoiImage);
// 		qDebug() << "Beam image received. time stamp" << timeThisPicture << "ms = " << timeThisPicture.toMSecsSinceEpoch() << "Previous" << m_LastReceivedPictureCreationDate.toMSecsSinceEpoch() << "ms since last = " << "ms since last = " << m_LastReceivedPictureCreationDate.time().msecsTo(timeThisPicture.time());
		break;
	case Back:
		m_ImageIn.insert(whichImageType, aoiImage);
// 		qDebug() << "Back image received. time stamp" << timeThisPicture << "ms = " << timeThisPicture.toMSecsSinceEpoch() << "ms scince last = " << "Previous" << m_LastReceivedPictureCreationDate.toMSecsSinceEpoch() << "ms since last = " << m_LastReceivedPictureCreationDate.time().msecsTo(timeThisPicture.time());
		break;
	case Suspicious:
//		m_ImageIn.clear();
// 		qDebug() << "Suspicious image received. time stamp" << timeThisPicture << "ms = " << timeThisPicture.toMSecsSinceEpoch() << "ms scince last = " << "Previous" << m_LastReceivedPictureCreationDate.toMSecsSinceEpoch() << "ms since last = " << m_LastReceivedPictureCreationDate.time().msecsTo(timeThisPicture.time());
		break;
	}
	m_ImageMutex.unlock();

	if(whichImageType == Back) {
		start();
//TryThread 		GImageDouble computedImage = ComputeAbsorption(m_DisplayRailDown, m_DisplayRailUp);
//TryThread 		// emitting the signal
//TryThread 		emit OutputImageDouble(computedImage);
	}

	m_LastReceivedPictureCreationDate = timeThisPicture;
}

void GAbsorptionImageProcessor::run()
{
	GImageDouble computedImage = ComputeAbsorption(m_DisplayRailDown, m_DisplayRailUp);
	// emitting the signal
	emit OutputImageDouble(computedImage);
}

/////////////////////////////////////////////////////////////////////
/*!
This function is called only when an image is received. 

If the image is received a long time after the previous picture, we assume it is the first picture 
of a batch. It is internally represented by the type ImageType::Atom.

The time to consider for the timeout is set using SetBatchTimeOut_ms().

\return: GAbsorptionImageProcessor::ImageType : the guessing of the type of the image based on when this function was called.
*////////////////////////////////////////////////////////////////////
GAbsorptionImageProcessor::ImageType GAbsorptionImageProcessor::WichImageMustThatBe(QDateTime dateTimePictureCreated)
{
	// this function is called when an image is received
	// if it was a long time after the previous picture, we assume it is the first picture of a batch
	int timeSinceLastPictureTODAY = m_LastReceivedPictureCreationDate.time().msecsTo(dateTimePictureCreated.time());
	int daysScinceLastPicture = m_LastReceivedPictureCreationDate.daysTo(dateTimePictureCreated);

	ImageType PreviousImageType = m_CurrentImageType;

	if(timeSinceLastPictureTODAY > m_BatchTimeOut_ms || daysScinceLastPicture > 0) {
		m_CurrentImageType = Atom;
	}
	else {
		switch(PreviousImageType) {
		case Atom:
			m_CurrentImageType = Beam;
			break;
		case Beam:
			m_CurrentImageType = Back;
			break;
		case Back: //TryThread
			m_CurrentImageType = Atom;
			break;
		default:
			//TryThread
			m_CurrentImageType = Atom;
// 			qDebug() << "Suspicious image and previous image type = " << PreviousImageType;
// 			qDebug() << "m_LastReceivedPictureCreationDate = " << m_LastReceivedPictureCreationDate;
// 			qDebug() << "dateTimePictureCreated = " << dateTimePictureCreated;
// 			qDebug() << "timeSinceLastPictureTODAY = " << timeSinceLastPictureTODAY;
			break;
		}
	}
	//TryThread
	if(isRunning()) 
		m_CurrentImageType = Suspicious;

	return m_CurrentImageType;
}

/////////////////////////////////////////////////////////////////////
/*!
It uses the pictures in that are internally stored in m_ImageIn. 
The calculation involves the pictures internally labeled as having type "Atom", "Beam", and "Back, 
but it could also involve the pixel size and other camera calibration data if a saturated absorption is computed.

Let's not forget that the computation involves :
* making an array of real numbers that contains the accurate and meaningful data
* making a 8-bit QImage (rescaled to a range of 0-255 values) that is going to be interpreted by the display.

\return: GImageDouble : The image representing the optical density
\param:  double RailDownForDisplay : the value of the optical density that corresponds to the value 0 for the QImage sent to the display.
\param:  double RailUp255ForDisplay : the value of the optical density that corresponds to the value 255 for the QImage sent to the display.
*////////////////////////////////////////////////////////////////////
GImageDouble GAbsorptionImageProcessor::ComputeAbsorption( double RailDownForDisplay, double RailUp255ForDisplay )
{
	m_ImageMutex.lock();
	GImageDouble imAtom = m_ImageIn.value(Atom);//.Clone();
	GImageDouble imBeam = m_ImageIn.value(Beam);//.Clone();
	GImageDouble imBack = m_ImageIn.value(Back);//.Clone();
	m_ImageMutex.unlock();
	// if the image is invalid
	if(imAtom.format() == QImage::Format_Invalid) {
		qWarning() << "The image \"with atoms\" seems to be invalid. 9115816";
		return GImageDouble();
	}
	if(imBeam.format() == QImage::Format_Invalid) {
		qWarning() << "The image \"with just the beam\" seems to be invalid. 9115817";
		return GImageDouble();
	}
	if(imBack.format() == QImage::Format_Invalid) {
		qWarning() << "The \"background\" image seems to be invalid. 9115818";
		return GImageDouble();
	}
	QSize imSize = imAtom.size();
	// the image to return
	GImageDouble OpticalDensity(imSize.width(), imSize.height());

	double* dOD = OpticalDensity.DoubleArray().data();
	double* dAtom = imAtom.DoubleArray().data();
	double* dBeam = imBeam.DoubleArray().data();
	double* dBack = imBack.DoubleArray().data();
	int Npix = OpticalDensity.DoubleArray().size();
	for(int i = 0; i < Npix; i++) {
			dOD[i] = qLn((dBeam[i] - dBack[i]) / (dAtom[i] - dBack[i]));
	}
	OpticalDensity.FillQimageFromUsingDoubleArray(RailDownForDisplay, RailUp255ForDisplay);
	IncrementCountProcessed();

	return OpticalDensity;
}