#ifndef GIMAGE2DGAUSSFITTER_H
#define GIMAGE2DGAUSSFITTER_H

#include "device.h"
#include "param.h"
#include "LabExeImaging/GImageProcessor.h"

/////////////////////////////////////////////////////////////////////
//! \brief The GImage2DGaussFitter class implements an image processor that run a fitting routine for a 2D-Gaussian function.
/*!
*/
class GImage2DGaussFitter : public GImageProcessor
{
	Q_OBJECT

public:
	GImage2DGaussFitter(QObject *parent, QString uniqueIdentifierName = "");
	~GImage2DGaussFitter();

protected:
	//! Re-implemented
	virtual void PopulateDeviceWidget(GDeviceWidget* theDeviceWidget);
	//! Re-implemented
	void run();

public:
	//! Re-implemented
	virtual void UpdateGraphicsItem();

public:
	void InputImage(QImage imageIn);

public slots:
	//! Function executed in the main thread in order to update, all at once, the output result of the fit. This is to prevent race conditions that could arise from the direct connection of the ValueUpdated signals (They could behave like Qt::QueuedConnection).
	void UpdateFinalResultValues( GVectorDouble finalValues );

protected:
	//! Re-implemented
	void ProcessImageAOIed(const GImageDouble & aoiImage);

private:
	//! the ellipse to be drawn on the image
	QGraphicsEllipseItem* m_pEllipse; 
	GImageDouble m_CurrentImageIn;

public:
	GParamBucket m_Variables;
	GParamBucket m_InitialValues;
	GParamDouble m_Offset
		, m_Ampl
		, m_X0
		, m_Y0
		, m_SigmaX
		, m_SigmaY;
	QVector<bool> m_FitMask;
	GParamDouble m_IniOffset
		, m_IniAmpl
		, m_IniX0
		, m_IniY0
		, m_IniSigmaX
		, m_IniSigmaY;
};

void Fit( GImageDouble imageIn, GImage2DGaussFitter* ptr );

#endif // GIMAGE2DGAUSSFITTER_H
