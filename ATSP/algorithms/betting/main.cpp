#include "mainwindow.h"
#include <QApplication>
#include "workerthread.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.setGraphTitle( MainWindow::GraphRect::_1st, "ATSP Path cost");
    w.setGraphTitle( MainWindow::GraphRect::_2nd, "Game Statistics");
    w.setGraphTitle( MainWindow::GraphRect::_3rd, "Player: rounds alive");
    w.setGraphTitle( MainWindow::GraphRect::_4th, "Player: consecutive wins");

    w.show();

    WorkerThread thread(w,1000);
    thread.start();

    return a.exec();
}
