#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QDesktopWidget>
#include <QScreen>
#include <QMessageBox>
#include <QMetaEnum>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("BetAlgorithm");
    statusBar()->clearMessage();

    setupGraph();
    centerAndResize();

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setGraphTitle(MainWindow::GraphRect rect, const QString & str)
{
    this->GraphRects[rect]->axis(QCPAxis::atTop)->setLabel(str);
}

void MainWindow::addData(MainWindow::Graph graph, double key, double value)
{
    ui->customPlot->graph(graph)->addData(key,value);
}

void MainWindow::setData(MainWindow::Graph graph, const QVector<QCPGraphData> & data)
{
    ui->customPlot->graph(graph)->data()->set(data);
}

void MainWindow::setYaxisRange(MainWindow::GraphRect rect, double lower, double upper)
{
    this->GraphRects[rect]->axis(QCPAxis::atLeft)->setRange(lower,upper);
}

void MainWindow::replot()
{

    for (int i = 0; i < ui->customPlot->graphCount(); i++ )
    {
       ui->customPlot->graph(i)->rescaleAxes(true);
    }

    GraphRects[2]->axis(QCPAxis::atLeft)->ticker()->setTickCount(2);
    GraphRects[3]->axis(QCPAxis::atLeft)->ticker()->setTickCount(2);

    ui->customPlot->replot();
}



void MainWindow::setupGraph()
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
    GraphCost->setPen( QPen(QColor("#8B0000")));//darkred

    GraphWinners = customPlot->addGraph(
                GraphRects[1]->axis(QCPAxis::atBottom),
                GraphRects[1]->axis(QCPAxis::atLeft));
    GraphWinners->setPen( QPen(QColor("#FF8C00")));//darkorange
    GraphWinners->setName("Winners");

    GraphLosers = customPlot->addGraph(
                GraphRects[1]->axis(QCPAxis::atBottom),
                GraphRects[1]->axis(QCPAxis::atLeft));
    GraphLosers->setPen( QPen(QColor("#2F4F4F")));//darkslategray
    GraphLosers->setName("Losers");

    GraphOutsiders = customPlot->addGraph(
                GraphRects[1]->axis(QCPAxis::atBottom),
                GraphRects[1]->axis(QCPAxis::atLeft));
    GraphOutsiders->setPen( QPen(QColor("#663399"),1,Qt::DashLine));//Rebeccapurple
    GraphOutsiders->setName("Outsiders");

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
    GraphLosers->addToLegend(legend);
    GraphOutsiders->addToLegend(legend);

    // create plotabbles for 3rd and 4th graphs
    // and set them to show bars

    GraphPlayerRoundsAlive = customPlot->addGraph(
                GraphRects[2]->axis(QCPAxis::atBottom),
                GraphRects[2]->axis(QCPAxis::atLeft));
    GraphRects[2]->axis(QCPAxis::atBottom)->setRange(0.5,30.5);
    GraphRects[2]->axis(QCPAxis::atLeft)->setSubTicks(true);

    //QSharedPointer<QCPAxisTickerFixed> intTicker(new QCPAxisTickerFixed);
    //intTicker->setTickStep(1.0);
    //intTicker->setScaleStrategy(QCPAxisTickerFixed::ssMultiples);

    //GraphRects[2]->axis(QCPAxis::atBottom)->setTicker(intTicker);


    GraphPlayerRoundsAlive->setLineStyle(QCPGraph::lsImpulse);
    GraphPlayerRoundsAlive->setPen(QPen(QColor("#008080"), 30));

    GraphPlayerConsecutiveWins = customPlot->addGraph(
                GraphRects[3]->axis(QCPAxis::atBottom),
                GraphRects[3]->axis(QCPAxis::atLeft));

    GraphRects[3]->axis(QCPAxis::atBottom)->setRange(0.5,30.5);
    GraphRects[3]->axis(QCPAxis::atLeft)->setSubTicks(true);
    //GraphRects[3]->axis(QCPAxis::atBottom)->setTicker(intTicker);

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



}

void MainWindow::centerAndResize()
{
    // get the dimension available on this screen
//    QSize availableSize = qApp->desktop()->availableGeometry().size();
//    int width = availableSize.width();
//    int height = availableSize.height();
//    //qDebug() << "Available dimensions " << width << "x" << height;
//    width *= 0.9; // 90% of the screen size
//    height *= 0.9; // 90% of the screen size
//    //qDebug() << "Computed dimensions " << width << "x" << height;
    QSize newSize( 1000, 618 );

    setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            newSize,
            qApp->desktop()->availableGeometry()
        )
    );
}
void MainWindow::show()
{
   QMainWindow::show();
   QApplication::processEvents();
}

void MainWindow::setMessage(const QString& msg)
{
    ui->statusBar->showMessage( msg );
}
