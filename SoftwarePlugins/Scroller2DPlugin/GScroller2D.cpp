#include "GScroller2D.h"
#include "GCrosshairItem.h"

//! [Initialize the parameters]
GScroller2D::GScroller2D(QObject *parent, QString uniqueIdentifierName /* = "" */)
	: GProgDevice(parent, uniqueIdentifierName)
    , m_sceneRect(0,0,500,500)
    , m_pScene(new QGraphicsScene(m_sceneRect, this))
    , m_pSceneRectItem(new QGraphicsRectItem(m_sceneRect))
    , m_vParamBucket("vertical", this)
    , m_hParamBucket("horizontal", this)
    , m_pCrosshair(new GCrosshairItem(m_pSceneRectItem, this))
{
    m_hParamBucket.ParamNum()->SetHardLimits(0,500);
    m_vParamBucket.ParamNum()->SetHardLimits(0,500);
}

GScroller2D::~GScroller2D()
{

}

/////////////////////////////////////////////////////////////////////
/*!
Populates a widget provided by a workbench in order to represent (and be adequately connected to) this GScroller2D. 
Layouts are used to make the widget react correctly to re-sizing.
The easiest way to connect the button and spinboxes to the actual instance of the corresponding parameter 
is to use the method GParamXXXX::ProvideNew----Widget(), that does all the necessary connections 
automatically (which would be the equivalent of this PopulateDeviceWidget(), but for a single parameter).
\param:  GDeviceWidget * theDeviceWidget : the parent widget in the gui.
*////////////////////////////////////////////////////////////////////
//[PopulateDeviceWidgetImplementation]
void GScroller2D::PopulateDeviceWidget(GDeviceWidget* theDeviceWidget )
{
    QGraphicsView* m_pView = new QGraphicsView(m_pScene, theDeviceWidget);
    m_pView->setSceneRect(QRectF(0,0,500,500));

    m_pScene->addItem(m_pSceneRectItem);
    m_pSceneRectItem->setPos(0,0);
    m_pCrosshair->setPos(0,0);
    m_pCrosshair->setFlag(QGraphicsItem::ItemIsSelectable);
    m_pCrosshair->setFlag(QGraphicsItem::ItemIsFocusable);
    m_pCrosshair->setFlag(QGraphicsItem::ItemIsMovable);

    m_pScene->addItem(m_pCrosshair);

    QSlider* hSlider = new QSlider(Qt::Horizontal, theDeviceWidget);
    hSlider->setMinimum(0);
    hSlider->setMaximum(500);
    //hSlider->setTracking(true);
    QSlider* vSlider = new QSlider(Qt::Vertical, theDeviceWidget);
    vSlider->setMinimum(0);
    vSlider->setMaximum(500);
    //vSlider->setTracking(true);

    QGridLayout* pGridLay = new QGridLayout();
    theDeviceWidget->AddSubLayout(pGridLay);

    pGridLay->addWidget(m_pView, 0, 0, 1, 2);
    pGridLay->addWidget(vSlider, 0, 2);
    pGridLay->addWidget(hSlider, 1, 0, 1, 2);
    pGridLay->addWidget(m_vParamBucket.ProvideParamBucketWidget(theDeviceWidget), 2, 1);
    pGridLay->addWidget(m_hParamBucket.ProvideParamBucketWidget(theDeviceWidget), 2, 0);

    connect(this, SIGNAL(XChanged(int)), hSlider, SLOT(setValue(int)));
    //connect(this, SIGNAL(XChanged(int)), m_hParamBucket, SLOT(SetParamValue(int)));
    connect(this, SIGNAL(YChanged(int)), vSlider, SLOT(setValue(int)));

    //connect(hSlider, SIGNAL(sliderMoved(int)), this, SLOT(MoveCrosshair(int)));
}

void GScroller2D::Event_CrosshairMoved(QPointF CrosshairCenterPos)
{
    emit XChanged((int)CrosshairCenterPos.rx());
    emit YChanged((int)CrosshairCenterPos.ry());
    m_hParamBucket.SetParamValue(CrosshairCenterPos.rx());
    m_vParamBucket.SetParamValue(CrosshairCenterPos.ry());
}

void GScroller2D::MoveCrosshair(int newPos)
{
    qDebug() << (qreal)newPos;
    //m_pCrosshair->setPos((qreal)newPos,m_pCrosshair->pos().ry());
}
