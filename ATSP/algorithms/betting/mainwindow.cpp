#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>
#include "TSPLibLoader/TSPLibLoader.h"
#include "betting_phase1.h"
#include <memory>
#include <sstream>
#include <iomanip>
#include <QtMath>

using namespace atsp;
using std::stringstream;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupGraph();
    centerAndResize();
    connect( ui->pushButtonRun, SIGNAL(released()), this, SLOT(buttonRunClick()));
    base::fast_srand();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupGraph()
{

    setupGraphPahse1();
    setupGraphPhase2();

}

void MainWindow::setupGraphPahse1()
{
    QCustomPlot *customPlot = ui->customPlot;

    // configure axis rect:
    // clear default axis rect so we can start from scratch
    customPlot->plotLayout()->clear();

    // 1st graph: cost x iteraction (dynamic x axis)
    // 2nd graph: winners/losers/not-in x iteraction (dynamic x axis)
    // 3rd graph: rounds alive x player
    // 4th graph: rounds winning x player

    QCPMarginGroup *marginGroup = new QCPMarginGroup(customPlot);

    QPen noPen((Qt::PenStyle(Qt::NoPen)));

    for (int i = 0; i < 4; ++i)
    {
        GraphRects[i] = new QCPAxisRect(customPlot);

        GraphRects[i]->setMinimumSize(0,100);

        GraphRects[i]->axis(QCPAxis::atTop)->setVisible(true);
        GraphRects[i]->axis(QCPAxis::atTop)->setLabel(QString("Graph %1").arg(i) );
        GraphRects[i]->axis(QCPAxis::atTop)->setTicks(false);
        GraphRects[i]->axis(QCPAxis::atTop)->setBasePen( noPen );
        GraphRects[i]->axis(QCPAxis::atLeft)->ticker()->setTickCount(5);
        GraphRects[i]->axis(QCPAxis::atLeft)->setSubTicks(false);

        customPlot->plotLayout()->addElement(i, 0, GraphRects[i]);
        GraphRects[i]->setMarginGroup(QCP::msLeft | QCP::msRight, marginGroup);

    }

    foreach (QCPAxisRect *rect, customPlot->axisRects())
    {
      foreach (QCPAxis *axis, rect->axes())
      {
        axis->setLayer("axes");
        axis->grid()->setLayer("grid");
      }
    }

    GraphRects[0]->setMinimumSize(0,200);
    GraphRects[1]->setMinimumSize(0,200);

    GraphRects[0]->axis(QCPAxis::atLeft)->setLabel("Path Cost");
    GraphRects[1]->axis(QCPAxis::atLeft)->setLabel("#of Players");
    GraphRects[2]->axis(QCPAxis::atLeft)->setLabel("Rounds");
    GraphRects[3]->axis(QCPAxis::atLeft)->setLabel("Wins");



    // create and configure plottables:
    GraphCost = customPlot->addGraph(
                GraphRects[0]->axis(QCPAxis::atBottom),
                GraphRects[0]->axis(QCPAxis::atLeft));
    GraphCost->setPen( QPen(QColor("#8B0000"),2));//darkred

    GraphWinners = customPlot->addGraph(
                GraphRects[1]->axis(QCPAxis::atBottom),
                GraphRects[1]->axis(QCPAxis::atLeft));
    GraphWinners->setPen( QPen(QColor("#FF8C00"),2));//darkorange
    GraphWinners->setName("Winners");

    GraphPlayed = customPlot->addGraph(
                GraphRects[1]->axis(QCPAxis::atBottom),
                GraphRects[1]->axis(QCPAxis::atLeft));
    GraphPlayed->setPen( QPen(QColor("#4286f4"),2));
    GraphPlayed->setName("Played");

    GraphBroken = customPlot->addGraph(
                GraphRects[1]->axis(QCPAxis::atBottom),
                GraphRects[1]->axis(QCPAxis::atLeft));
    GraphBroken->setPen( QPen(QColor("#f141f4"),2,Qt::DashLine));
    GraphBroken->setName("Broken");

    // custom legend of the 2nd graph
    // 1st, set the system to not add newly created legends to default legend
    customPlot->setAutoAddPlottableToLegend(false);

    //create new legend
    QCPLegend *legend = new QCPLegend();
    GraphRects[1]->insetLayout()->addElement(legend,Qt::AlignTop | Qt::AlignRight);
    legend->setLayer("legend");
    legend->setBorderPen(noPen);
    legend->setBrush( QBrush( QColor(50,50,50,32)));

    // set it to show side-by-side
    legend->setFillOrder(QCPLayoutGrid::FillOrder::foColumnsFirst);
    // add legends
    GraphWinners->addToLegend(legend);
    GraphPlayed->addToLegend(legend);
    GraphBroken->addToLegend(legend);

    // create plotabbles for 3rd and 4th graphs
    // and set them to show bars

    GraphPlayerRoundsAlive = customPlot->addGraph(
                GraphRects[2]->axis(QCPAxis::atBottom),
                GraphRects[2]->axis(QCPAxis::atLeft));
    GraphRects[2]->axis(QCPAxis::atBottom)->setRange(0.5,30.5);
    GraphRects[2]->axis(QCPAxis::atLeft)->setSubTicks(true);
    GraphRects[2]->axis(QCPAxis::atBottom)->setSubTicks(true);

    GraphPlayerRoundsAlive->setLineStyle(QCPGraph::lsImpulse);
    GraphPlayerRoundsAlive->setPen(QPen(QColor("#008080"), 30));

    GraphPlayerConsecutiveWins = customPlot->addGraph(
                GraphRects[3]->axis(QCPAxis::atBottom),
                GraphRects[3]->axis(QCPAxis::atLeft));

    GraphRects[3]->axis(QCPAxis::atBottom)->setRange(0.5,30.5);
    GraphRects[3]->axis(QCPAxis::atLeft)->setSubTicks(true);
    GraphRects[3]->axis(QCPAxis::atBottom)->setSubTicks(true);

    GraphPlayerConsecutiveWins->setLineStyle(QCPGraph::lsImpulse);
    GraphPlayerConsecutiveWins->setPen(QPen(QColor("#808080"), 30));


    // the maximum overall value of the last two graphs
    GraphPlayerRoundsAliveMax = customPlot->addGraph(
                GraphRects[2]->axis(QCPAxis::atBottom),
                GraphRects[2]->axis(QCPAxis::atLeft));
    GraphPlayerRoundsAliveMax->setPen( QPen(QColor("#FF4500"),1,Qt::DashLine));

    GraphPlayerConsecutiveWinsMax = customPlot->addGraph(
                GraphRects[3]->axis(QCPAxis::atBottom),
                GraphRects[3]->axis(QCPAxis::atLeft));
    GraphPlayerConsecutiveWinsMax->setPen( QPen(QColor("#FF4500"),1,Qt::DashLine));

    this->GraphRects[MainWindow::GraphRect::_1st]->\
            axis(QCPAxis::atTop)->setLabel("ATSP Path cost");
    this->GraphRects[MainWindow::GraphRect::_2nd]->\
            axis(QCPAxis::atTop)->setLabel("Satistics");
    this->GraphRects[MainWindow::GraphRect::_3rd]->\
            axis(QCPAxis::atTop)->setLabel("Player: rounds alive");
    this->GraphRects[MainWindow::GraphRect::_4th]->\
            axis(QCPAxis::atTop)->setLabel("Player: consecutive wins");

    customPlot->setInteractions(QCP::iRangeZoom);

}

void MainWindow::setupGraphPhase2()
{


}

void MainWindow::centerAndResize()
{
    QSize newSize( 1200, 618 );

    setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            newSize,
            qApp->desktop()->availableGeometry()
        )
                );
}

void MainWindow::showExceptionDialog(const QString &msg)
{
    QMessageBox msgBox;

    msgBox.setText( QString("An Exception has occurred: " ) + msg);
    msgBox.setInformativeText("Do you want to quit the application?");
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);

    if ( msgBox.exec() == QMessageBox::Yes )
    {
        this->close();
    }

}

using ::bet::Player;
using ::bet::PlayerStats;
using atsp::bet::BetAlgorithm1;

void MainWindow::buttonRunClick()
try
{

    stringstream msg;

    // problem data
    const QString   fname( ui->lineEditFile->text() );
    const uint      restarts = ui->lineEditRestarts->text().toUInt();
    const uint      iters = ui->lineEditIters->text().toUInt();
    const uint      trSize = ui->lineEditTrSize->text().toUInt();
    const uint      numPicks = ui->lineEditPicks->text().toUInt();
    const uint      numPlayers = ui->lineEditPlayers->text().toUInt();
    const double    minBet = ui->lineEditMinBet->text().toDouble();
    const double    initialBankroll = ui->lineEditBankroll->text().toDouble();
    const uint      pickPolicy = ui->lineEditPickPolicy->text().toUInt();

    Data data;
    data.load( atsp::TSPLibLoader(fname.toStdString().c_str()));

    std::unique_ptr<Player[]> players( new Player[numPlayers] );

    Player::setGameParameters(data.getSize(),minBet,initialBankroll);

    for (uint i = 0; i < numPlayers; ++i)
        players[i].reset();

    BetAlgorithm1 bet1(trSize, numPicks, pickPolicy, players.get(), numPlayers);


    QTime timer;
    timer.start();

    uint count = 0;

    ui->customPlot->graph(Graph::Cost)->data()->clear();
    ui->customPlot->graph(Graph::Won)->data()->clear();
    ui->customPlot->graph(Graph::Played)->data()->clear();
    ui->customPlot->graph(Graph::Broke)->data()->clear();
    ui->customPlot->graph(Graph::RoundsAlive)->data()->clear();
    ui->customPlot->graph(Graph::ConsecutiveWins)->data()->clear();
    ui->customPlot->graph(Graph::RoundsAliveMax)->data()->clear();
    ui->customPlot->graph(Graph::ConsecutiveWinsMax)->data()->clear();

    Path current(data.getSize());
    atsp::randomize(current);
    Path best = current;
    uint all_min = atsp::getLength(data,best);
    uint max = all_min;


    uint refresh = (restarts * iters)/100;

    //bet1.setAlgorithm(BetAlgorithm1::Algoritm::Basic);

    for (uint run = 0; run < restarts; run++)
    {
        for (uint iter = 0; iter < iters; iter++)
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
            ui->customPlot->graph(Graph::Cost)->addData(key,value);
            if ( count % refresh == 0)
            {
                ui->customPlot->graph(Graph::Played)->addData(key, PlayerStats::getRoundPlayers());
                ui->customPlot->graph(Graph::Won)->addData(key,PlayerStats::getRoundWinners());
                ui->customPlot->graph(Graph::Broke)->addData(key, PlayerStats::getRoundBroken());
            }
            count++;
        }
        atsp::randomize(current);
    }

    for (int i = 0; i < ui->customPlot->graphCount(); i++ )
    {
       ui->customPlot->graph(i)->rescaleAxes(false);
    }


    GraphRects[0]->axis(QCPAxis::atLeft)->setRange(0,max);
    GraphRects[1]->axis(QCPAxis::atLeft)->setRange(0,numPlayers * 1.1);

    GraphRects[2]->axis(QCPAxis::atLeft)->ticker()->setTickCount(2);
    GraphRects[3]->axis(QCPAxis::atLeft)->ticker()->setTickCount(2);

    uint maxGA = 0; // will be used to set the graph's y range
    uint maxCW = 0;

    for(uint i = 0; i < numPlayers; i++)
    {
        const ::bet::PlayerStats & stats = players[i].getStats();

        ui->customPlot->graph(Graph::RoundsAlive)->addData(i, stats.getGamesAlive());
        ui->customPlot->graph(Graph::ConsecutiveWins)->addData(i,stats.getConsecutiveWins());

        ui->customPlot->graph(Graph::RoundsAliveMax)->addData(i,stats.getMaxGamesAlive());
        ui->customPlot->graph(Graph::ConsecutiveWinsMax)->addData(i,stats.getMaxConsecutiveWins());

        if (stats.getMaxGamesAlive() > maxGA) maxGA = stats.getMaxGamesAlive();
        if (stats.getMaxConsecutiveWins() > maxCW) maxCW = stats.getMaxConsecutiveWins();

    }
    GraphRects[2]->axis(QCPAxis::atBottom)->setRange(-0.5,numPlayers-0.5);
    GraphRects[3]->axis(QCPAxis::atBottom)->setRange(-0.5,numPlayers-0.5);
    GraphRects[2]->axis(QCPAxis::atLeft)->setRange(0,maxGA*1.1);
    GraphRects[3]->axis(QCPAxis::atLeft)->setRange(0,maxCW*1.1);

    // adjust the bar width pf the bar graphs
    int barWidth = GraphRects[MainWindow::GraphRect::_3rd]->width();

    barWidth = qFloor(static_cast<double>(barWidth) / numPlayers);
    barWidth = barWidth > 0 ? barWidth:1;

    GraphPlayerConsecutiveWins->setPen(QPen(QColor("#808080"), barWidth));
    GraphPlayerRoundsAlive->setPen(QPen(QColor("#008080"), barWidth));

    ui->customPlot->replot();

    msg.str(std::string());
    msg << "Elapsed Time: " << static_cast<double>(timer.elapsed())/1000.0 << "s ";
    msg << "Initial Value: " << max;
    msg << " Final Result: "<< all_min;
    double diff = max - all_min;
    msg << " Improvement: " << static_cast<uint>(diff);
    msg << " (-" << std::fixed << std::setprecision(0) << diff*100/max << "%)";

    ui->statusBar->showMessage(msg.str().c_str());
}
catch (QException &e)
{
    showExceptionDialog(e.what());
}
catch (std::exception &e)
{
    showExceptionDialog(e.what());
}
catch(...)
{
    showExceptionDialog("Unknown exception in <Run>");
}
void MainWindow::show()
{
   QMainWindow::show();
}
