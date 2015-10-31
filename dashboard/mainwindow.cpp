#include "mainwindow.h"

#include <QtGui/QStatusBar>
#include <QtGui/QMenuBar>
#include <QtGui/QMenu>
#include <QtGui/QToolBar>
#include <QtGui/QAction>
#include <QtGui/QBoxLayout>
#include <QtGui/QFormLayout>
#include <QtGui/QLabel>
#include <QtGui/QGroupBox>
#include <QtCore/QDebug>

#include "speedo.h"

MainWindow::MainWindow(QWidget *parent)
  : QMainWindow(parent) {
  this->setCentralWidget(new QWidget(this));

  
  // setup default status bar message
  this->statusBar()->showMessage("Disconnected");

  // setup toolbar
  QToolBar *pConnectionToolbar = this->addToolBar("Connection");
  pConnectionToolbar->addAction("Connect", this, SLOT(connectWithTrionic()));
  connected = false;
  this->statusBar()->showMessage("Welcome to Trionicnet Dashboard...");
  this->setWindowTitle("Dasboard");

  // setup numbers layout
  QBoxLayout *pCentralLayout = new QBoxLayout(QBoxLayout::TopToBottom, this->centralWidget());
  QBoxLayout *pEngineLayout = new QBoxLayout(QBoxLayout::LeftToRight);
  pCentralLayout->addLayout(pEngineLayout);
  QGroupBox *pGroupBox = new QGroupBox("Temperatures", this->centralWidget());
  QFormLayout *pFormLayout = new QFormLayout(pGroupBox);
  pFormLayout->addRow(new QLabel("Water Temperature:"), new QLabel("92"));
  pFormLayout->addRow(new QLabel("Air Temperature"), new QLabel("30"));
  pFormLayout->addRow(new QLabel("Combustion Temperature") ,new QLabel("600"));
  pEngineLayout->addWidget(pGroupBox);

  QGroupBox *pGroupBox2 = new QGroupBox("Engine", this->centralWidget());
  QFormLayout *pFormLayout2 = new QFormLayout(pGroupBox2);
  pFormLayout2->addRow(new QLabel("Injector lvl"), new QLabel("1.26"));
  pFormLayout2->addRow(new QLabel("Accelerator lvl"), new QLabel("100"));
  pFormLayout2->addRow(new QLabel("Air mass intake"), new QLabel("2000"));
  pEngineLayout->addWidget(pGroupBox2);

  QGroupBox *pGroupBox3 = new QGroupBox("Dashboard", this->centralWidget());
  pCentralLayout->addWidget(pGroupBox3);

  // setup graphics scene
  m_pScene = new QGraphicsScene(pGroupBox3);
  m_pScene->setBackgroundBrush(QBrush(Qt::gray));
  m_pView = new QGraphicsView(m_pScene, pGroupBox3);
  Speedo speedo(m_pScene, pGroupBox3);
}

MainWindow::~MainWindow() {

}

void MainWindow::connectWithTrionic() {
  qDebug("User wants to mate with trionic...");
  this->statusBar()->showMessage("Connecting...");
}
