#include "workerthread.h"
#include <ctime>
#include <limits>
#include <cmath>

#include "TSPLibLoader/TSPLibLoader.h"
#include "betting_phase1.h"
#include <memory>
#include <sstream>

using namespace atsp;
using atsp::bet::Player;
using std::stringstream;

void WorkerThread::run()
try
{

}
catch( std::runtime_error & e)
{
    stringstream msg;
    msg.clear();
    msg << "Runtime Error: " << e.what();
    _mainWindow.setMessage(msg.str().c_str());
    this->exit();
}

//void WorkerThread::run()
//{
//   qsrand(QDateTime::currentSecsSinceEpoch());
//   double last = static_cast<double>(qrand()) / RAND_MAX;
//   //this->msleep(100);
//   QTime timer;
//   timer.start();

//   QVector<QCPGraphData> RoundsAlive;
//   QVector<QCPGraphData> ConsecWins;
//   QVector<QCPGraphData> RoundsAliveMax;
//   QVector<QCPGraphData> ConsecWinsMax;

//   for(uint i = 1; i < 31; i++)
//   {
//       RoundsAlive << QCPGraphData(i,0);
//       ConsecWins << QCPGraphData(i,0);
//       RoundsAliveMax << QCPGraphData(i,0);
//       ConsecWinsMax << QCPGraphData(i,0);
//   }

//   for(int count = 0; count <= 100000; ++count )
//   {
//       double value = last + (static_cast<double>(qrand()) / RAND_MAX - 0.5);
//       int winners = qrand() % 30;
//       int loosers = qrand() % (30-winners);
//       int notins = 30 - winners - loosers;

//       notins = notins > 0 ? notins : 0;

//       mainWindow.addData(MainWindow::Graph::Cost,count,value);

//       if (count % updateRate == 0)
//       {

//           mainWindow.addData(MainWindow::Graph::Winners, count, winners);
//           mainWindow.addData(MainWindow::Graph::Losers, count, loosers);
//           mainWindow.addData(MainWindow::Graph::Out,count,notins);

//           for(int i = 0; i < 30; i++)
//           {
//                bool won = ((static_cast<double>(qrand()) / RAND_MAX) > 0.3);

//                if ( won )
//                {
//                    RoundsAlive[i].value += 1.0;
//                    ConsecWins[i].value += 1.0;
//                }
//                else
//                {
//                   bool killed = ( (static_cast<double>(qrand()) / RAND_MAX) > 0.95);
//                   if (killed) RoundsAlive[i].value = 0.0;
//                   ConsecWins[i].value = 0.0;
//                }
//                if (RoundsAlive[i].value > RoundsAliveMax[i].value)
//                    RoundsAliveMax[i].value = RoundsAlive[i].value;
//                if (ConsecWins[i].value > ConsecWinsMax[i].value)
//                    ConsecWinsMax[i].value = ConsecWins[i].value;
//           }
//           mainWindow.setData(MainWindow::Graph::RoundsAlive,RoundsAlive);
//           mainWindow.setData(MainWindow::Graph::ConsecutiveWins,ConsecWins);
//           mainWindow.setData(MainWindow::Graph::RoundsAliveMax, RoundsAliveMax);
//           mainWindow.setData(MainWindow::Graph::ConsecutiveWinsMax, ConsecWinsMax);

//           mainWindow.replot();
//       }

//       last = value;
//   }
//   mainWindow.setMessage(
//               QString("Elapsed Time: %1s")
//               .arg(static_cast<double>(timer.elapsed())/1000.0,0,'f',2)
//               );

//}

WorkerThread::WorkerThread(MainWindow & mw, QObject *parent, uint ur):
    QThread(parent),_mainWindow(mw),_updateRate(ur), _fname(nullptr),
    _nReps(0),_nIters(0),_trSize(0), _numPicks(0), _numPlayers(0),
    _minBet(0.0), _initialBankroll(0.0)
{
}

void WorkerThread::setRunParams(char * tspFname,
                                uint nIters, uint nReps,
                                uint trSize, uint numPicks,
                                uint numPlayers, double minBet, double initialBankroll)
{
    _fname = tspFname;
    _nIters = nIters;
    _nReps = nReps;
    _trSize = trSize;
    _numPicks = numPicks;
    _numPlayers = numPlayers;
    _minBet = minBet;
    _initialBankroll = initialBankroll;
}



