#include "sharedmemory.h"

#include <QtCore/QTimer>

extern "C" {
#include "distribution_areas.h"
}

#include <QDebug>

SharedMemory::SharedMemory(QObject *parent)
  : QObject(parent) {
  m_previousEngineSpeed = 0;
  int handtag = 0;
  void *pData = get_port(port_engine_speed, &handtag, sizeof(data_item_header)+4);
  m_pEngineSpeed = static_cast<unsigned int *>(pData)+sizeof(data_item_header);
  QTimer *pTimer = new QTimer(this);
  connect(pTimer, SIGNAL(timeout()), this, SLOT(checkIfDataHasChanged()));
  pTimer->start(16);
}

SharedMemory::~SharedMemory() {

}

// public slots:
void SharedMemory::checkIfDataHasChanged() {
  if (m_previousEngineSpeed != *m_pEngineSpeed) {
    qDebug() << "P DATTA MASIN: " << *m_pEngineSpeed;
    m_previousEngineSpeed = *m_pEngineSpeed;
    emit engineSpeedChanged(static_cast<int>(*m_pEngineSpeed));
  }
}
