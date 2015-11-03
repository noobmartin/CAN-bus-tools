#ifndef SHAREDMEMORY_H
#define SHAREDMEMORY_H

#include <QtCore/QObject>
#include <QtCore/QVariant>
class SharedMemory : public QObject {
  Q_OBJECT
public:
  explicit SharedMemory(QObject *parent = 0);
  ~SharedMemory();

signals:
  void engineSpeedChanged(const int engineSpeed);

public slots:
  void checkIfDataHasChanged();

private:
  unsigned int *m_pEngineSpeed;
  unsigned int m_previousEngineSpeed;

};

#endif // SHAREDMEMORY_H
