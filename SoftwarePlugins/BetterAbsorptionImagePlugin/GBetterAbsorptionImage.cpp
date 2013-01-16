#include "GBetterAbsorptionImage.h"

int MaxChebyshevLength = 5;

GBetterAbsorptionImage::GBetterAbsorptionImage(QObject *parent, QString uniqueIdentifierName /*= ""*/)
	: GImageProcessor(parent, uniqueIdentifierName)
	, m_BatchTimeOut_ms(500)
	, m_CurrentImageType(Suspicious)
	, m_DisplayRailDown("Disp-min", this)
	, m_DisplayRailUp("Disp-max", this)
	, m_DoCorrectAmplitude("Correct amplitude", this)
	, m_CorrectAmplPercent("[%]", this, GParam::ReadOnly)
	, m_DoCorrectPosition("Correct position", this)
	, m_CorrectPosX("dX", this, GParam::ReadOnly)
	, m_CorrectPosY("dY", this, GParam::ReadOnly)
	, m_AoiIn(5)
{
	// this is an image provider
	m_IsImageProvider = true;
	m_DisplayRailUp = 1.0;

	m_DisplayRailDown.SetHardLimits(-9.9, 99.9);
	m_DisplayRailUp.SetHardLimits(-9.9, 99.9);

	m_CorrectPosX.SetHardLimits(-99, 99);
	m_CorrectPosY.SetHardLimits(-99, 99);

	m_CorrectAmplPercent.SetHardLimits(-99.9, 999.9);
//	m_CorrectAmplPercent.SetDisplayDecimals(1);
}

GBetterAbsorptionImage::~GBetterAbsorptionImage()
{
	//TryThread
	wait(2000);
	terminate();
	m_ImageIn.clear();
}

void GBetterAbsorptionImage::PopulateDeviceWidget(GDeviceWidget* theDeviceWidget )
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

	QHBoxLayout* ErrLay = new QHBoxLayout();
	QFormLayout* XerrLay = new QFormLayout();
	QFormLayout* YerrLay = new QFormLayout();
	ErrLay->addLayout(XerrLay);
	ErrLay->addLayout(YerrLay);
	XerrLay->addRow(m_CorrectPosX.ProvideNewLabel(theDeviceWidget), m_CorrectPosX.ProvideNewParamSpinBox(theDeviceWidget));
	YerrLay->addRow(m_CorrectPosY.ProvideNewLabel(theDeviceWidget), m_CorrectPosY.ProvideNewParamSpinBox(theDeviceWidget));
	QFormLayout* correctionLayout = new QFormLayout();
	QFormLayout* AmpcorrLay = new QFormLayout();
	AmpcorrLay->addRow(m_CorrectAmplPercent.ProvideNewLabel(theDeviceWidget), m_CorrectAmplPercent.ProvideNewParamSpinBox(theDeviceWidget));
	correctionLayout->addRow(m_DoCorrectPosition.ProvideNewParamCheckBox(theDeviceWidget), ErrLay);
	correctionLayout->addRow(m_DoCorrectAmplitude.ProvideNewParamCheckBox(theDeviceWidget), AmpcorrLay);
	theDeviceWidget->AddSubLayout(correctionLayout);
}

void GBetterAbsorptionImage::PopulateSettings( QSettings& inQsettings )
{
	GImageProcessor::PopulateSettings(inQsettings);
	inQsettings.setValue("dispMin", (double)m_DisplayRailDown);
	inQsettings.setValue("dispMax", (double)m_DisplayRailUp);
}

void GBetterAbsorptionImage::InterpretSettings( QSettings& fromQsettings )
{
	GImageProcessor::InterpretSettings(fromQsettings);
	m_DisplayRailDown = fromQsettings.value("dispMin", 0.0).toDouble();
	m_DisplayRailUp = fromQsettings.value("dispMax", 5.0).toDouble();
}

void GBetterAbsorptionImage::ProcessImageFull(const GImageDouble & fullImage, const QRect & theAoiInTheFullImage)
{
	QDateTime timeThisPicture = fullImage.DateTimeCreated();
	// update the m_CurrentImageType
	WichImageMustThatBe(timeThisPicture);
	switch(m_CurrentImageType) {
	case Suspicious:
		break;
	case Atom:
		m_ImageMutex.lock();
		m_ImageIn.clear();
		m_ImageMutex.unlock();
	default:
		m_ImageMutex.lock();
		m_ImageIn[m_CurrentImageType] = fullImage;
		m_ImageMutex.unlock();
	}

	m_LastReceivedPictureCreationDate = timeThisPicture;
}

void GBetterAbsorptionImage::ProcessImageAOIed( const GImageDouble & aoiImage )
{
	switch(m_CurrentImageType) {
	case Suspicious:
		break;
	case Atom:
		m_ImageMutex.lock();
		m_AoiIn.fill(GImageDouble());
		m_ImageMutex.unlock();
	default:
		m_ImageMutex.lock();
		m_AoiIn[m_CurrentImageType] = aoiImage;
		m_ImageMutex.unlock();
	}

	if(m_CurrentImageType == Back) {
		start();
	}
}

void GBetterAbsorptionImage::run()
{
	double factorBeam = 1.0;
	QPoint bestTranslationBeam(0,0);

	m_ImageMutex.lock();
// 	m_AoiIn[Atom] -= m_AoiIn[Back];
// 	m_AoiIn[Beam] -= m_AoiIn[Back];
// 	m_ImageIn[Atom] -= m_ImageIn[Back];
// 	m_ImageIn[Beam] -= m_ImageIn[Back];
	m_ImageMutex.unlock();

	if(m_DoCorrectPosition) {
		bestTranslationBeam = CorrectPosition(MaxChebyshevLength);
	}
	m_ImageMutex.lock();
	m_ImageIn[Beam] = m_ImageIn[Beam].DataShifted(bestTranslationBeam);
	m_AoiIn[Beam] = m_AoiIn[Beam].DataShifted(bestTranslationBeam);
	m_ImageMutex.unlock();

	if(m_DoCorrectAmplitude) {
		factorBeam = CorrectionFactorAmplitude();
	}
	m_ImageMutex.lock();
	m_ImageIn[Beam] *= factorBeam;
	m_ImageMutex.unlock();

	m_CorrectAmplPercent = factorBeam * 100.0 - 100.0;
	m_CorrectPosX = bestTranslationBeam.x();
	m_CorrectPosY = bestTranslationBeam.y();

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

\return: GBetterAbsorptionImage::ImageType : the guessing of the type of the image based on when this function was called.
*////////////////////////////////////////////////////////////////////
GBetterAbsorptionImage::ImageType GBetterAbsorptionImage::WichImageMustThatBe(QDateTime dateTimePictureCreated)
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
GImageDouble GBetterAbsorptionImage::ComputeAbsorption( double RailDownForDisplay, double RailUp255ForDisplay )
{
	m_ImageMutex.lock();
	GImageDouble imAtom = m_ImageIn[Atom];
	GImageDouble imBeam = m_ImageIn[Beam];
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
	QSize imSize = imAtom.size();
	// the image to return
	GImageDouble OpticalDensity(imSize.width(), imSize.height());

	double* dOD = OpticalDensity.DoubleArray().data();
	double* dAtom = imAtom.DoubleArray().data();
	double* dBeam = imBeam.DoubleArray().data();
	int Npix = OpticalDensity.DoubleArray().size();
	for(int i = 0; i < Npix; i++) {
		if(dAtom[i] > 0.0 && dBeam[i] > 0.0) {
			dOD[i] = qLn(dBeam[i] / dAtom[i]);
		} else {
			dOD[i] = qQNaN();
		}
	}
	OpticalDensity.FillQimageFromUsingDoubleArray(RailDownForDisplay, RailUp255ForDisplay);
	IncrementCountProcessed();

	return OpticalDensity;
}

double GBetterAbsorptionImage::CorrectionFactorAmplitude()
{
	double factorRet = 1.0;
	m_ImageMutex.lock();
	GImageDouble imAtom = m_AoiIn[Atom];
	GImageDouble imBeam = m_AoiIn[Beam];
	m_ImageMutex.unlock();

	double* dAtom = imAtom.DoubleArray().data();
	double* dBeam = imBeam.DoubleArray().data();
	int Npix = imBeam.DoubleArray().count();
	int pxTot = 0;
	double sumLn = 1.0;
	for(int i = 0; i < Npix; i++) {
		if(dAtom[i] > 0.0 && dBeam[i] > 0.0) {
			sumLn *= (dBeam[i] / dAtom[i]);
			pxTot++;
		}
	}
	if(!pxTot)
		return 1.0;
	sumLn = qLn(sumLn);

	factorRet = qExp(-sumLn / double(pxTot));
	return factorRet;
}

QPoint GBetterAbsorptionImage::CorrectPosition( int maxChebyshevLength )
{
	m_ImageMutex.lock();
	GImageDouble imAtom = m_AoiIn[Atom];
	GImageDouble imBeam = m_AoiIn[Beam];
	m_ImageMutex.unlock();

	int wid = imAtom.width();
	int hei = imAtom.height();

	QMap<double, QPoint> point_dev;

	for(int jTrans = -maxChebyshevLength; jTrans <= maxChebyshevLength ; jTrans++) {
		for(int iTrans = -maxChebyshevLength; iTrans <= maxChebyshevLength ; iTrans++) {
			QPoint pointTrans(iTrans, jTrans);
			double* dAtom = imAtom.DoubleArray().data();
			GImageDouble imBeamShifted = imBeam.DataShifted(pointTrans);
			double* dBeam = imBeamShifted.DoubleArray().data();

			int Npix = (wid - 2 * maxChebyshevLength) * (hei - 2 * maxChebyshevLength);
			double sumLn = 0.0;
			double sumLnSquared = 0.0;
			int iTot = 0;
			int pxTot = 0;
			for(int j = maxChebyshevLength; j < hei - maxChebyshevLength; j++) {
				for(int i = maxChebyshevLength; i < wid - maxChebyshevLength; i++) {
					iTot = i + j * wid;
					if(dAtom[iTot] > 0.0 && dBeam[iTot] > 0.0) {
						double theOD = qLn(dBeam[iTot] / dAtom[iTot]);
						sumLn += theOD;
						theOD *= theOD;
						sumLnSquared += theOD;
						pxTot++;
					}
				}
			}
			if(!pxTot)
				continue;
			double dNpixTot = double(pxTot);
			sumLn /= dNpixTot;
			sumLnSquared /= dNpixTot;
			double stdDev = sumLnSquared - sumLn * sumLn;
			// if for a same stdDev, we have another point, we pick the one closest to (0,0)
			if(point_dev.contains(stdDev)) {
				QPoint pointAlreadyStDev = point_dev.value(stdDev);
				if(pointTrans.manhattanLength() > pointAlreadyStDev.manhattanLength()) {
					continue;
				}
			}
			point_dev.insert(stdDev, pointTrans);
		}
	}

	if(point_dev.isEmpty())
		return QPoint(0, 0);

	double theMin = point_dev.keys().first();
	return point_dev.value(theMin);
}