#include "workerthread.h"
#include <ctime>
#include <limits>
#include <cmath>

#include "base/random.h"
#include "atsp/data.h"
#include "TSPLibLoader/TSPLibLoader.h"
#include "atsp/path.h"
#include "betting_phase1.h"

void WorkerThread::run()
try
{

}
catch( std::exception & e)
{
    QMessageBox mb;
    mb.setText(e.what());
    mb.exec();
    this->exit();
}
catch(...)
{
    QMessageBox mb;
    mb.setText("Unknown exception caught in main()");
    mb.exec();
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

WorkerThread::WorkerThread(MainWindow & mw, int ur):mainWindow(mw),updateRate(ur)
{
}

