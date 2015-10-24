#include "speedo.h"

Speedo::Speedo(QGraphicsScene *pScene, QObject *parent) :
  QObject(parent),
  m_pScene(pScene) {
  m_pRect = m_pScene->addRect(0, 0, 200, 100);
  QGraphicsRectItem *pInsideRect = new QGraphicsRectItem(m_pRect, m_pScene);
  pInsideRect->setBrush(QBrush(Qt::red));
  pInsideRect->setPen(QPen(QColor(0,0,0,0)));
  pInsideRect->setRect(1, 1, 75*2-1, 99);
  m_pRect->setToolTip("Speedo");

  pInsideRect->setOpacity(1);
}

QGraphicsItem *Speedo::graphicsItem() {
  return m_pRect;
}
