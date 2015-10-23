#ifndef SPEEDO_H
#define SPEEDO_H

#include <QtGui/QGraphicsRectItem>
#include <QtGui/QGraphicsScene>

class Speedo : public QObject {

public:
  explicit Speedo(QGraphicsScene *pScene, QObject *parent = 0);

  QGraphicsItem *graphicsItem();

public slots:

private:
  QGraphicsRectItem *m_pRect;
  QGraphicsScene *m_pScene;
};

#endif // SPEEDO_H
