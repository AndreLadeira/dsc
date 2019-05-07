#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
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

    enum GraphRect
    {
         _1st = 0,_2nd,_3rd,_4th
    };
    enum Graph
    {
        Cost = 0, Won, WonAvg, Played, Broke, RoundsAlive, ConsecutiveWins,
        RoundsAliveMax, ConsecutiveWinsMax
    };
    enum GraphPhase2
    {
        Greedy = 0, BetRoundsAlive, BetRecentPerformance
    };
    void show();


private:

    Ui::MainWindow *ui;

    QCPAxisRect *GraphRects[4];

    QCPGraph    *GraphCost;
    QCPGraph    *GraphWinners;
    QCPGraph    *GraphWinnersMovAvg;
    QCPGraph    *GraphPlayed;
    QCPGraph    *GraphBroken;
    QCPGraph    *GraphPlayerRoundsAlive;
    QCPGraph    *GraphPlayerRoundsAliveMax;
    QCPGraph    *GraphPlayerConsecutiveWins;
    QCPGraph    *GraphPlayerConsecutiveWinsMax;

    QCPGraph    *GraphPhase2Greedy;
    QCPGraph    *GraphPhase2BetOp1;
    QCPGraph    *GraphPhase2BetOp2;

    void setupGraph();
    void setupGraphPahse1();
    void setupGraphPhase2();
    void centerAndResize();


    void showExceptionDialog(const QString & msg);

private slots:
    void buttonRunClick();
    void resetGraphZoom(QCPAbstractPlottable*,int,QMouseEvent*);
    void cpMouseDblClick(QMouseEvent *event);
    void cpMousePress();
};

#endif // MAINWINDOW_H
