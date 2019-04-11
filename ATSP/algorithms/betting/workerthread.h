#ifndef WORKERTHREAD_H
#define WORKERTHREAD_H

#include <QThread>
#include "mainwindow.h"

class WorkerThread : public QThread
{
    Q_OBJECT
protected:
    void run();
public:
    WorkerThread(MainWindow &, int updateRate = 1000);
private:
    MainWindow & mainWindow;
    int          updateRate;
};

#endif // WORKERTHREAD_H
