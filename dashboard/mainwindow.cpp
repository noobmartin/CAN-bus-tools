#include "mainwindow.h"

#include <QtGui/QStatusBar>
#include <QtGui/QMenuBar>
#include <QtGui/QMenu>
#include <QtGui/QToolBar>
#include <QtGui/QAction>

#include <QtCore/QDebug>

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent) {
  this->statusBar()->showMessage("Disconnected");

  // setup toolbar
  QToolBar *pConnectionToolbar = this->addToolBar("Connection");
  QIcon icon(":/icons/connect-icon.png");
  QAction *pConnectAction = pConnectionToolbar->addAction(icon, "Connect", this, SLOT(connectWithTrionic()));
  pConnectAction->setIconVisibleInMenu(true);
  pConnectionToolbar->addAction("Disconnect", this, SLOT(disconnectFromTrionic()));

}

MainWindow::~MainWindow() {

}

void MainWindow::connectWithTrionic() {
  qDebug("User wants to mate with trionic...");
  this->statusBar()->showMessage("Connecting...");
}

void MainWindow::disconnectFromTrionic() {
  qDebug("User wants to stop mating with trionic...");
}
