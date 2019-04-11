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

void MainWindow::replot()
{
//    foreach (QCPAxisRect *rect, ui->customPlot->axisRects())
//    {
//        rect->setRa
//    }
    //GraphCost->keyAxis()->setRange(0,);

    for(int i = 0; i < ui->customPlot->graphCount(); ++i)
    {
        ui->customPlot->graph(i)->rescaleAxes(true);
    }
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



    /*
     *
  customPlot->legend->setFont(QFont("Helvetica",9));
  // set locale to english, so we get english decimal separator:
  customPlot->setLocale(QLocale(QLocale::English, QLocale::UnitedKingdom));
  // add confidence band graphs:
  customPlot->addGraph();
  QPen pen;
  pen.setStyle(Qt::DotLine);
  pen.setWidth(1);
  pen.setColor(QColor(180,180,180));
  customPlot->graph(0)->setName("Confidence Band 68%");
  */

    //subGraphRandom->setLineStyle(QCPGraph::lsImpulse);
    //subGraphRandom->setPen(QPen(QColor("#FFA100"), 1.5));


    foreach (QCPAxisRect *rect, customPlot->axisRects())
    {
      foreach (QCPAxis *axis, rect->axes())
      {
        axis->setLayer("axes");
        axis->grid()->setLayer("grid");
      }
    }


    //qsrand(QDateTime::currentSecsSinceEpoch());

    //connect(&Timer, SIGNAL(timeout()), this, SLOT(timerSlot()));
    //Time.start();
    //Timer.start(0);
    /*

    //customPlot->plotLayout()->setRowStretchFactor(1, 2);
    // prepare axis rects that will be placed in the sublayout:
    QCPAxisRect *subRectLeft = new QCPAxisRect(customPlot, false); // false means to not setup default axes
    QCPAxisRect *subRectRight = new QCPAxisRect(customPlot, false);
    subLayout->addElement(0, 0, subRectLeft);
    subLayout->addElement(0, 1, subRectRight);
    subRectRight->setMaximumSize(100, 100); // make bottom right axis rect size fixed 100x100
    subRectRight->setMinimumSize(100, 100); // make bottom right axis rect size fixed 100x100
    // setup axes in sub layout axis rects:
    subRectLeft->addAxes(QCPAxis::atBottom | QCPAxis::atLeft);
    subRectRight->addAxes(QCPAxis::atBottom | QCPAxis::atRight);
    subRectLeft->axis(QCPAxis::atLeft)->ticker()->setTickCount(2);
    subRectRight->axis(QCPAxis::atRight)->ticker()->setTickCount(2);
    subRectRight->axis(QCPAxis::atBottom)->ticker()->setTickCount(2);
    subRectLeft->axis(QCPAxis::atBottom)->grid()->setVisible(true);
    // synchronize the left and right margins of the top and bottom axis rects:
    QCPMarginGroup *marginGroup = new QCPMarginGroup(customPlot);
    subRectLeft->setMarginGroup(QCP::msLeft, marginGroup);
    subRectRight->setMarginGroup(QCP::msRight, marginGroup);
    wideAxisRect->setMarginGroup(QCP::msLeft | QCP::msRight, marginGroup);
    // move newly created axes on "axes" layer and grids on "grid" layer:
    foreach (QCPAxisRect *rect, customPlot->axisRects())
    {
      foreach (QCPAxis *axis, rect->axes())
      {
        axis->setLayer("axes");
        axis->grid()->setLayer("grid");
      }
    }

    // prepare data:
    QVector<QCPGraphData> dataCos(21), dataGauss(50), dataRandom(100);
    QVector<double> x3, y3;
    qsrand(3);
    for (int i=0; i<dataCos.size(); ++i)
    {
      dataCos[i].key = i/(double)(dataCos.size()-1)*10-5.0;
      dataCos[i].value = qCos(dataCos[i].key);
    }
    for (int i=0; i<dataGauss.size(); ++i)
    {
      dataGauss[i].key = i/(double)dataGauss.size()*10-5.0;
      dataGauss[i].value = qExp(-dataGauss[i].key*dataGauss[i].key*0.2)*1000;
    }
    for (int i=0; i<dataRandom.size(); ++i)
    {
      dataRandom[i].key = i/(double)dataRandom.size()*10;
      dataRandom[i].value = qrand()/(double)RAND_MAX-0.5+dataRandom[qMax(0, i-1)].value;
    }
    x3 << 1 << 2 << 3 << 4;
    y3 << 2 << 2.5 << 4 << 1.5;

    // create and configure plottables:
    QCPGraph *mainGraphCos = customPlot->addGraph(wideAxisRect->axis(QCPAxis::atBottom), wideAxisRect->axis(QCPAxis::atLeft));
    mainGraphCos->data()->set(dataCos);
    mainGraphCos->valueAxis()->setRange(-1, 1);
    mainGraphCos->rescaleKeyAxis();
    mainGraphCos->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, QPen(Qt::black), QBrush(Qt::white), 6));
    mainGraphCos->setPen(QPen(QColor(120, 120, 120), 2));
    QCPGraph *mainGraphGauss = customPlot->addGraph(wideAxisRect->axis(QCPAxis::atBottom), wideAxisRect->axis(QCPAxis::atLeft, 1));
    mainGraphGauss->data()->set(dataGauss);
    mainGraphGauss->setPen(QPen(QColor("#8070B8"), 2));
    mainGraphGauss->setBrush(QColor(110, 170, 110, 30));
    mainGraphCos->setChannelFillGraph(mainGraphGauss);
    mainGraphCos->setBrush(QColor(255, 161, 0, 50));
    mainGraphGauss->valueAxis()->setRange(0, 1000);
    mainGraphGauss->rescaleKeyAxis();

    QCPGraph *subGraphRandom = customPlot->addGraph(subRectLeft->axis(QCPAxis::atBottom), subRectLeft->axis(QCPAxis::atLeft));
    subGraphRandom->data()->set(dataRandom);
    subGraphRandom->setLineStyle(QCPGraph::lsImpulse);
    subGraphRandom->setPen(QPen(QColor("#FFA100"), 1.5));
    subGraphRandom->rescaleAxes();

    QCPBars *subBars = new QCPBars(subRectRight->axis(QCPAxis::atBottom), subRectRight->axis(QCPAxis::atRight));
    subBars->setWidth(3/(double)x3.size());
    subBars->setData(x3, y3);
    subBars->setPen(QPen(Qt::black));
    subBars->setAntialiased(false);
    subBars->setAntialiasedFill(false);
    subBars->setBrush(QColor("#705BE8"));
    subBars->keyAxis()->setSubTicks(false);
    subBars->rescaleAxes();
    // setup a ticker for subBars key axis that only gives integer ticks:
    QSharedPointer<QCPAxisTickerFixed> intTicker(new QCPAxisTickerFixed);
    intTicker->setTickStep(1.0);
    intTicker->setScaleStrategy(QCPAxisTickerFixed::ssMultiples);
    subBars->keyAxis()->setTicker(intTicker);

    */
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
