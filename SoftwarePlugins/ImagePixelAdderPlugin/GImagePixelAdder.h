#ifndef GIMAGEPIXELADDER_H
#define GIMAGEPIXELADDER_H

#include "device.h"
#include "param.h"
#include "LabExeImaging/GImageProcessor.h"

/////////////////////////////////////////////////////////////////////
//! \brief The GImagePixelAdder class implements a very simple image processor that computes the sum and average of the pixels.
/*!
*/
class GImagePixelAdder : public GImageProcessor
{
	Q_OBJECT

public:
	GImagePixelAdder(QObject *parent, QString uniqueIdentifierName = "");
	~GImagePixelAdder();

protected:
	//! Reimplemented
	virtual void PopulateDeviceWidget(GDeviceWidget* theDeviceWidget);
	//! Re-implemented
	void run();
	//! Re-implemented
	void UpdateGraphicsItem() {}

protected:
	//! Reimplemented
	void ProcessImageAOIed(const GImageDouble & aoiImage);

private:
	GParamDouble m_SumPix;
	GParamDouble m_AvePix;
	GParamDouble m_StdDevPix;
};


#endif // GIMAGEPIXELADDER_H
