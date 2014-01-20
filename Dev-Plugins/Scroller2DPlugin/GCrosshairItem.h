#ifndef GCROSSHAIRITEM_H
#define GCROSSHAIRITEM_H

#include <QGraphicsRectItem>
#include <QGraphicsScene>
#include <QVariant>
#include <QRectF>

class GScroller2D;

class GCrosshairItem : public QGraphicsRectItem
{
public:
    GCrosshairItem(QGraphicsRectItem* pParentItem, GScroller2D* theDevice);
    virtual ~GCrosshairItem() {}
    QRectF m_RectF;
    GScroller2D* m_pDevice;
    void MoveCrosshair(QPointF newPos);
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value);
};

#endif // GCROSSHAIRITEM_H
