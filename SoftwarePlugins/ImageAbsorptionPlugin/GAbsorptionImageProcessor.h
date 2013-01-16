#ifndef GABSORPTIONIMAGEPROCESSOR_H
#define GABSORPTIONIMAGEPROCESSOR_H
#include "ImageAbsorptionPlugin_global.h"

#include "device.h"
#include "param.h"
#include "LabExeImaging/GImageProcessor.h"
#include <QElapsedTimer>

/////////////////////////////////////////////////////////////////////
//! \brief The GAbsorptionImageProcessor class implements an image processor
/*!
 It receives images from a camera and outputs a computed GImageDouble object that represent the absorption.
*/
class IMAGEABSORPTIONPLUGIN_EXPORT GAbsorptionImageProcessor : public GImageProcessor
{
	Q_OBJECT

	//! The different type of images that can be considered.
	typedef enum e_ImageType {Atom, Beam, Back, Calc, Suspicious} ImageType;

public:
	GAbsorptionImageProcessor(QObject *parent, QString uniqueIdentifierName = "");
	~GAbsorptionImageProcessor();

protected:
	//! Re-implemented
	void PopulateSettings( QSettings& inQsettings );
	//! Re-implemented
	void InterpretSettings( QSettings& fromQsettings );

protected:
	//! Reimplemented
	void PopulateDeviceWidget(GDeviceWidget* theDeviceWidget);
	//! Re-implemented
	void ProcessImageAOIed(const GImageDouble & aoiImage);
	//! This function uses timing consideration in order to guess what image is being received.
	ImageType WichImageMustThatBe(QDateTime dateTimePictureCreated);
	//! sets the timeout time in ms, after which a picture is considered to "must-be-from-the-next-batch"
	void SetBatchTimeOut_ms(int val) { m_BatchTimeOut_ms = val; }
	//! This function calculates the absorption by using the pictures received.
	GImageDouble ComputeAbsorption( double RailDownForDisplay, double RailUp255ForDisplay );
	//! Re-implemented
	void run();

private:
	//! The images needed to compute
	QMap<ImageType, GImageDouble> m_ImageIn;
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
	//! mutex to protect the access to shared images
	QMutex m_ImageMutex;
};

#endif // GABSORPTIONIMAGEPROCESSOR_H
