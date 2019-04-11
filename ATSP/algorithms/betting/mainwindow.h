#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qcustomplot.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void showMessage(const QString &);

    enum GraphRect
    {
         _1st = 0,_2nd,_3rd,_4th
    };
    enum Graph
    {
        Cost = 0, Winners, Losers, Out, RoudsAlive, ConsecutiveWins
    };

    void setGraphTitle(GraphRect, const QString&);
    void addData(Graph, double key, double value);
    void replot();
    void show();
    void setMessage(const QString&);

private:

    Ui::MainWindow *ui;

    QCPAxisRect *GraphRects[4];

    QCPGraph    *GraphCost;
    QCPGraph    *GraphWinners;
    QCPGraph    *GraphLosers;
    QCPGraph    *GraphOutsiders;
    QCPGraph    *GraphPlayerRoundsAlive;
    QCPGraph    *GraphPlayerConsecutiveWins;



    void setupGraph();
    void centerAndResize();
};

#endif // MAINWINDOW_H
