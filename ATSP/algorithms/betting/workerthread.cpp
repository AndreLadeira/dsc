#include "workerthread.h"

void WorkerThread::run()
{
   qsrand(QDateTime::currentSecsSinceEpoch());
   double last = static_cast<double>(qrand()) / RAND_MAX;
   //this->msleep(100);
   QTime timer;
   timer.start();

   for(int count = 0; count <= 100000; ++count )
   {
       double value = last + (static_cast<double>(qrand()) / RAND_MAX - 0.5);
       int winners = qrand() % 30;
       int loosers = qrand() % (30-winners);
       int notins = 30 - winners - loosers;

       notins = notins > 0 ? notins : 0;

       mainWindow.addData(MainWindow::Graph::Cost,count,value);


       if (count % updateRate == 0)
       {

           mainWindow.addData(MainWindow::Graph::Winners, count, winners);
           mainWindow.addData(MainWindow::Graph::Losers, count, loosers);
           mainWindow.addData(MainWindow::Graph::Out,count,notins);
           mainWindow.replot();
       }

       last = value;
   }
   mainWindow.setMessage(
               QString("Elapsed Time: %1s")
               .arg(static_cast<double>(timer.elapsed())/1000.0,0,'f',2)
               );

}

WorkerThread::WorkerThread(MainWindow & mw, int ur):mainWindow(mw),updateRate(ur)
{
}

