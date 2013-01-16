#ifndef GABSORPTIONIMAGEPROCESSOR_H
#define GABSORPTIONIMAGEPROCESSOR_H
#include "BetterAbsorptionImagePlugin_global.h"

#include "device.h"
#include "param.h"
#include "LabExeImaging/GImageProcessor.h"
#include <QElapsedTimer>

/////////////////////////////////////////////////////////////////////
//! \brief The GBetterAbsorptionImage class implements an image processor
/*!
 It receives images from a camera and outputs a computed GImageDouble object that represent the absorption.
*/
class IMAGEABSORPTIONPLUGIN_EXPORT GBetterAbsorptionImage : public GImageProcessor
{
	Q_OBJECT

	//! The different type of images that can be considered.
	typedef enum e_ImageType {Atom, Beam, Back, Calc, Suspicious} ImageType;

public:
	GBetterAbsorptionImage(QObject *parent, QString uniqueIdentifierName = "");
	~GBetterAbsorptionImage();

protected:
	//! Re-implemented
	void PopulateSettings( QSettings& inQsettings );
	//! Re-implemented
	void InterpretSettings( QSettings& fromQsettings );

protected:
	//! Re-implemented
	void run();

	//! Reimplemented
	void PopulateDeviceWidget(GDeviceWidget* theDeviceWidget);
	//! Re-implemented. The AOI is the area used to correct the "Beam" image in order to have an averaged 0 and noiseless background of the computed image. If the AOI is the whole picture, an invalid QRect() is passed.
	void ProcessImageFull(const GImageDouble & fullImage, const QRect & theAoiInTheFullImage);
	//! Re-implemented in order to fill the m_AoiIn since (it is called right after ProcessImageFull())
	void ProcessImageAOIed(const GImageDouble & aoiImage);
	//! This function uses timing consideration in order to guess what image is being received.
	ImageType WichImageMustThatBe(QDateTime dateTimePictureCreated);
	//! sets the timeout time in ms, after which a picture is considered to "must-be-from-the-next-batch"
	void SetBatchTimeOut_ms(int val) { m_BatchTimeOut_ms = val; }
	//! This function calculates the absorption by using the pictures received.
	GImageDouble ComputeAbsorption( double RailDownForDisplay, double RailUp255ForDisplay );
	//! Try to change the amplitude of the "Beam" image in order to average the computed image to 0 on the AOI. Returns the multiplicator to use for the "Beam" image.
	double CorrectionFactorAmplitude();
	//! Try to change the position of the "Beam" image in order to bring down the std. dev. of the computed image pixels. Returns the corresponding shift of the "Beam" image.
	QPoint CorrectPosition(int maxChebyshevLength);

private:
	//! The images needed to compute
	QMap<ImageType, GImageDouble> m_ImageIn;
	//! The AOI sub-images needed to compute correct the "Beam" image.
	QVector<GImageDouble> m_AoiIn;
	//! The type of the current image being received
	ImageType m_CurrentImageType;
// 	//! A timer used to guess which image is being received
// 	QElapsedTimer m_pTimer;
	//! Date and time of the creation of the last picture received
	QDateTime m_LastReceivedPictureCreationDate;
	//! The time in ms after which a picture is considered to "must-be-from-the-next-batch". The default is 500 ms.
	int m_BatchTimeOut_ms;
	//! The param that holds the value of the OD that corresponds to 0/255 on the display
	GParamDouble m_DisplayRailDown;
	//! The param that holds the value of the OD that corresponds to 255/255 on the display
	GParamDouble m_DisplayRailUp;
	//! The param that holds the amplitude correction of the image "without" atoms (Beam) in order to have an averaged 0 background in the AOI.
	GParamDouble m_CorrectAmplPercent;
	GParamInt m_CorrectPosX;
	GParamInt m_CorrectPosY;
	//! Tells that we correct the amplitude of the "Beam" image
	GParamBool m_DoCorrectAmplitude;
	GParamBool m_DoCorrectPosition;
	//! mutex to protect the access to shared images
	QMutex m_ImageMutex;
};

#endif // GABSORPTIONIMAGEPROCESSOR_H
