#ifndef GUEYEIMAGEDISTRIBUTOR_H
#define GUEYEIMAGEDISTRIBUTOR_H

#include "imaging.h"
class GUeyeCamera;

/////////////////////////////////////////////////////////////////////
//! \brief The GUeyeImageDistributor class defines a type of GImageProcessor that uses the thread to wait for images from the camera.
/*!
It then converts then to QImage`s and send the OutputImage signal.
*/
class GUeyeImageDistributor : public GImageProcessor
{
	Q_OBJECT

public:
	GUeyeImageDistributor(GUeyeCamera *parent);
	~GUeyeImageDistributor();

	//! Re-implemented
	void StopProcessing() {m_ThreadWaitForImages = false;}

protected:
	//! re-implemented from QThread in order to initialize the variables and start waiting for images.
	void run();
	//! Reimplemented
	virtual void PopulateDeviceWidget(GDeviceWidget* theDeviceWidget) {}

private:
	//! Called when a new buffer was grabbed by the loop in the thread
	void BufferToTreat(char * pPix);

private:
	GUeyeCamera * m_pParentUeyeCamera;
	//! run switch
	volatile bool m_ThreadWaitForImages;
};

#endif // GUEYEIMAGEDISTRIBUTOR_H
