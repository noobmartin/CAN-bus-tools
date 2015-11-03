#include "testwidget.h"
#include <QtGui/QPainter>

TestWidget::TestWidget(QWidget *pParent) : QGroupBox("dashboard", pParent)
{

}

TestWidget::~TestWidget() {

}

void TestWidget::paintEvent(QPaintEvent *pPaintEvent) {
  QGroupBox::paintEvent(pPaintEvent);
//  pPaintEvent->accept();

  QPainter painter(this);
  painter.setViewport(this->rect());
  painter.setBrush(QBrush(Qt::black));
  painter.drawArc(75, 75, 150, 150, 0*16, 360*16);
  painter.drawArc(300, 75, 150, 150, 0*16, 360*16);
  painter.drawRect(215, 50, 100, 50);
  pPaintEvent->accept();
  this->adjustSize();
}
