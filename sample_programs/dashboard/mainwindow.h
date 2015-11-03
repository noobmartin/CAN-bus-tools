#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QtGui/QGraphicsScene>
#include <QtGui/QGraphicsView>

#include "sharedmemory.h"

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  MainWindow(QWidget *parent = 0);
  ~MainWindow();

private slots:
  void connectWithTrionic();

private:
  QGraphicsScene  *m_pScene;
  QGraphicsView   *m_pView;
  bool             connected;
  SharedMemory *m_pSharedMem;
};

#endif // MAINWINDOW_H
