#include "mainwindow.h"

#include <QtGui/QStatusBar>
#include <QtGui/QMenuBar>
#include <QtGui/QMenu>
#include <QtGui/QToolBar>
#include <QtGui/QAction>

#include <QtCore/QDebug>

#include "speedo.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent) {

  // setup graphics scene
  m_pScene = new QGraphicsScene(this);
  m_pScene->setBackgroundBrush(QBrush(Qt::gray));
  m_pView = new QGraphicsView(m_pScene, this);
  this->setCentralWidget(m_pView);

  Speedo speedo(m_pScene, this);

  // setup default status bar message
  this->statusBar()->showMessage("Disconnected");

  // setup toolbar
  QToolBar *pConnectionToolbar = this->addToolBar("Connection");
  pConnectionToolbar->addAction("Connect", this, SLOT(connectWithTrionic()));

  connected = false;
  this->statusBar()->showMessage("Welcome to Trionicnet Dashboard...");
  this->setWindowTitle("Dasboard");
}

MainWindow::~MainWindow() {

}

void MainWindow::connectWithTrionic() {
  qDebug("User wants to mate with trionic...");
  this->statusBar()->showMessage("Connecting...");
}
