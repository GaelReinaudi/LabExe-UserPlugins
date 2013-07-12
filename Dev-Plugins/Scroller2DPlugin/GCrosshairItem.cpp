#include "GCrosshairItem.h"
#include "GScroller2D.h"
#include <QDebug>

GCrosshairItem::GCrosshairItem(QGraphicsRectItem* pParentItem, GScroller2D* theDevice)
    : QGraphicsRectItem(pParentItem)
    , m_RectF(QRectF(0,0,50,50))
    , m_pDevice(theDevice)
{
    setBrush(QColor(0,0,0));
    setRect(m_RectF);
    setFlag(QGraphicsItem::ItemSendsScenePositionChanges);
}

QVariant GCrosshairItem::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == ItemPositionChange && scene()) {
             // value is the new position.
             QPointF newPos = value.toPointF();
             newPos += QPointF(25,25);
             QRectF rect = dynamic_cast<QGraphicsRectItem*>(parentItem())->rect();
             if (!rect.contains(newPos)) {
                 // Keep the item inside the scene rect.
                 newPos.setX(qMin(rect.right(), qMax(newPos.x(), rect.left())));
                 newPos.setY(qMin(rect.bottom(), qMax(newPos.y(), rect.top())));
                 m_pDevice->Event_CrosshairMoved(newPos);
                 return newPos - QPointF(25,25);
             }
         }
    m_pDevice->Event_CrosshairMoved(value.toPointF() + QPointF(25,25));
         return QGraphicsItem::itemChange(change, value);
}

void GCrosshairItem::MoveCrosshair(QPointF newPos)
{

}
