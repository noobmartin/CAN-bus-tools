#ifndef TESTWIDGET_H
#define TESTWIDGET_H

#include <QtGui/QGroupBox>
#include <QtGui/QPaintEvent>

class TestWidget : public QGroupBox {
public:
  TestWidget(QWidget *pParent = NULL);
  ~TestWidget();

  void paintEvent(QPaintEvent *pPaintEvent);
};

#endif // TESTWIDGET_H
