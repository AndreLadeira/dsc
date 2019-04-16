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
    stringstream msg;

    msg << "Running BET algoritm with "
        << _nReps << " restarts, "
        << _nIters << " iterations per restart, "
        << " removing/reinserting " << _trSize << " cities, with "
        << _numPicks << " picks and " << _numPlayers << " players / round";;

    QString str(msg.str().c_str());

    _mainWindow.setWindowTitle(str);

    Data data;
    data.load( atsp::TSPLibLoader(_fname) );
    base::fast_srand();

    Path current(data.getSize());
    Path best = current;
    std::unique_ptr<Player[]> players( new Player[_numPlayers] );

    Player::setGameParameters(data.getSize(),_minBet,_initialBankroll);

    for (uint i = 0; i < _numPlayers; ++i)
        players[i].reset();

    bet::BetAgorithm1 bet1(_trSize, _numPicks, players.get(), _numPlayers);
    uint all_min = atsp::getLength(data,best);

    QTime timer;
    timer.start();

    uint count = 0;

    if (!_updateRate)
        _updateRate = (_nReps * _nIters) / 10;

    for (uint run = 0; run < _nReps; run++)
    {
        atsp::randomize(current);

        for (uint iter = 0; iter < _nIters; iter++)
        {
            uint r = bet1.run(current, data);

            if ( r < all_min )
            {
                all_min = r;
                best = current;
            }
            double key = static_cast<double>(count);
            double value = static_cast<double>(all_min);
            // graph stuff
            _mainWindow.addData(MainWindow::Graph::Cost, key,value);
            if (count % _updateRate == 0)
            {
                _mainWindow.replot();
            }
            count++;

        }
    }
    _mainWindow.replot();
    msg.str(std::string());

    msg << "Elapsed Time: " << static_cast<double>(timer.elapsed())/1000.0;
    msg << " Final Result: "<< all_min;

    _mainWindow.setMessage(msg.str().c_str());
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



