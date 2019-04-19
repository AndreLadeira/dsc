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

    enum GraphRect
    {
         _1st = 0,_2nd,_3rd,_4th
    };
    enum Graph
    {
        Cost = 0, Won, Played, Broke, RoundsAlive, ConsecutiveWins,
        RoundsAliveMax, ConsecutiveWinsMax
    };
    void show();


private:

    Ui::MainWindow *ui;

    QCPAxisRect *GraphRects[4];

    QCPGraph    *GraphCost;
    QCPGraph    *GraphWinners;
    QCPGraph    *GraphPlayed;
    QCPGraph    *GraphBroken;
    QCPGraph    *GraphPlayerRoundsAlive;
    QCPGraph    *GraphPlayerRoundsAliveMax;
    QCPGraph    *GraphPlayerConsecutiveWins;
    QCPGraph    *GraphPlayerConsecutiveWinsMax;

    void setupGraph();
    void setupGraphPahse1();
    void setupGraphPhase2();
    void centerAndResize();

    void showExceptionDialog(const QString & msg);

private slots:
    void buttonRunClick();
};

#endif // MAINWINDOW_H
