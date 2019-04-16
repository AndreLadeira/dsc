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
    WorkerThread(MainWindow &, QObject *parent = nullptr, uint plotUpdateRate = 0);

    void setRunParams(char * tspFname, uint nIters, uint nReps, uint trSize = 2,
                      uint numPicks = 3, uint numPlayers = 30, double minBet = 1.0,
                      double initialBankroll = 1000.0);

private:
    MainWindow &        _mainWindow;
    uint                _updateRate; // update plots at avery _updateRate _nRuns
    char *              _fname;      // atsp data file name
    uint                _nReps;      // #of restarts (new initial random solutions)
    uint                _nIters;     // #of times a initial (random) solution is refined
    uint                _trSize;     // size of the sub-path that is removed and re-inserted
    uint                _numPicks;
    uint                _numPlayers;
    double              _minBet;
    double              _initialBankroll;
};

#endif // WORKERTHREAD_H
