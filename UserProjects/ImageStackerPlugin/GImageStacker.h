#ifndef GImageStacker_H
#define GImageStacker_H

#include "device.h"
#include "param.h"
#include "LabExeImaging/GImageProcessor.h"

/////////////////////////////////////////////////////////////////////
//! \brief The GImageStacker class implements an image processor
/*!
 It receives images from a camera and outputs a computed GImageDouble that is the sum of those images.
*/
class GImageStacker : public GImageProcessor
{
	Q_OBJECT

public:

	//! Constructor
	GImageStacker(QObject *parent, QString uniqueIdentifierName = "");
	~GImageStacker();

public slots:
	//! Resets the filter by setting the output equal to the input and emptying the history
	void Reset();

protected:
	//! Re-implemented to provide a new widget adequately connected to this GImageStacker.
	void PopulateDeviceWidget(GDeviceWidget* theDeviceWidget);
	//! Re-implemented
	void ProcessImageAOIed(const GImageDouble & aoiImage);
	//! Re-implemented
	void run();
	//! This function calculates the stacked image by adding or multiplying the m_StackedImage.
	GImageDouble StackUp( double RailDownForDisplay, double RailUp255ForDisplay );

private:
	//! the bucket for the input parameter
	GSingleParamBucket m_InputBucket;
	//! the output of the filter
	GParamDouble m_Output;
	//! the number of samples to average on.
	GParamInt m_SampleSize;
	//! a reset boolean that will provide a reset button
	GParamBool m_Reset;
	//! the history of the values of the parameters
// 	QList<double> m_History;
	QLinkedList<GImageDouble> m_History;
// 	QMap<double, GImageDouble> m_ImageIn;
	//! Date and time of the creation of the last picture received
	QDateTime m_LastReceivedPictureCreationDate;
	//! The param that holds the value of the OD that corresponds to 0/255 on the display
	GParamDouble m_DisplayRailDown;
	//! The param that holds the value of the OD that corresponds to 255/255 on the display
	GParamDouble m_DisplayRailUp;
	//! mutex to protect the access to shared images
	QMutex m_ImageMutex;
	//! received pictures during the isRunning. used so that we update the count of used picture accurately even if we do it by batches.
	int m_PicturesPutInHistorySinceLastStart;
};

#endif // GImageStacker_H
