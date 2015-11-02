#ifndef BOX_METER_H_
#define BOX_METER_H_

#include <QtGui/QGraphicsRectItem>
#include <QtGui/QGraphicsScene>

class BoxMeter : public QObject {

public:
  explicit BoxMeter(QGraphicsScene *pScene, double x=0, double y=0, double w=200, double=25, double value=0, double maxValue=100, QObject *parent = 0);

  QGraphicsItem *graphicsItem();

public slots:

private:
  QGraphicsRectItem *m_pRect;
  QGraphicsScene *m_pScene;

  double m_x;
  double m_y;
  double m_w;
  double m_h;
  double m_value;
  double m_maxValue;
};

#endif // BOX_METER_H_
