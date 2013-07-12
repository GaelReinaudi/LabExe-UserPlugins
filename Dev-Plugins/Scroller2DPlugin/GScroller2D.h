#ifndef GScroller2D_H
#define GScroller2D_H

#include "device.h"
#include "param.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QGraphicsRectItem>
#include <QRectF>
#include <QSlider>
#include "GCrosshairItem.h"
/////////////////////////////////////////////////////////////////////
//! \brief The GScroller2D class implements a GProgDevice.
/*!
This soft device allows you to define an input parameter by drag-and-dropping it in a param-bucket. 
When the input is updated, the average over the past \e n values is calculated and displayed at the output. 
The value of \e n is defined by a spin-box.
If there are not yet \e n values in the past history of the parameter, the average is made on all existing data. 
The reset button clears the history of the parameter.
*/
//[inheritance]
class GScroller2D : public GProgDevice
//[inheritance]
{
	Q_OBJECT

public:

//[constructor]
	//! Constructor
	GScroller2D(QObject *parent, QString uniqueIdentifierName = "");
//[constructor]
	~GScroller2D();


public slots:
    void MoveCrosshair(int newPos);
//![PopulateDeviceWidget]
protected:
	//! Re-implemented to provide a new widget adequately connected to this GScroller2D.
	void PopulateDeviceWidget(GDeviceWidget* theDeviceWidget);
//![PopulateDeviceWidget]

//! [variables]
private:
    QGraphicsScene* m_pScene;
    QRectF m_sceneRect;
    QGraphicsRectItem* m_pSceneRectItem;
    GSingleParamBucket m_vParamBucket;
    GSingleParamBucket m_hParamBucket;
    GCrosshairItem* m_pCrosshair;
protected:
    void Event_CrosshairMoved(QPointF CrosshairCenterPos);

signals:
    void XChanged(int xPos);
    void YChanged(int yPos);
friend class GCrosshairItem;
};

#endif // GScroller2D_H
