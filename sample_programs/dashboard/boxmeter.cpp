#include "boxmeter.h"

BoxMeter::BoxMeter(QGraphicsScene *pScene, double x, double y, double w, double h, double value, double maxValue, QObject *parent) :
  QObject(parent),
  m_pScene(pScene),
  m_x(x),
  m_y(y),
  m_w(w),
  m_h(h),
  m_value(value),
  m_maxValue(maxValue) {
  m_pRect = m_pScene->addRect(x, y, w, h);
  QGraphicsRectItem *pInsideRect = new QGraphicsRectItem(m_pRect, m_pScene);
  pInsideRect->setBrush(QBrush(Qt::red));
  pInsideRect->setPen(QPen(QColor(0,0,0,0)));
  pInsideRect->setRect(x+1, y+1, (m_w-1)*(m_value/m_maxValue), h-1);
  m_pRect->setToolTip("Meter");
  pInsideRect->setOpacity(1);
}

QGraphicsItem *BoxMeter::graphicsItem() {
  return m_pRect;
}
