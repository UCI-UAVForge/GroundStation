#include "graphwidget.h"
#include "ui_graphwidget.h"
#include <QTextStream> //For debugging

#include "telemetrypacket.h"

GraphWidget::GraphWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GraphWidget)
{
    ui->setupUi(this);
    GraphWidget::makePlot();
}

GraphWidget::~GraphWidget()
{
    delete ui;

}

void GraphWidget::makePlot()
{
    // Create mission
    Mission* mission = getNewMission();


    QVector<double> * vals = mission->getValuesForIndex(0);
    QVector<double> * val1 = mission->getValuesForID(6);

    // Test
//    this->vX = *((float*)(buffer + offset));// = this->vX;
//    this->vY = *((float*)(buffer + offset + 4));// = this->vY;
//    this->vZ = *((float*)(buffer + offset + 8));// = this->vZ;
//    this->pitch = *((float*)(buffer + offset + 12));// = this->pitch;
//    this->roll = *((float*)(buffer + offset + 16));// = this->roll;
//    this->yaw = *((float*)(buffer + offset + 20));// = this->yaw;
//    this->lat = *((double*)(buffer + offset + 24));// = this->lat;
//    this->lon = *((double*)(buffer + offset + 32));// = this->lon;
//    this->alt = *((float*)(buffer + offset + 40));// = this->alt;
//    this->heading = *((float*)(buffer + offset + 44));// = this->heading;

    QTextStream out(stdout);
    out << "vals size: " << (*vals)[1]<< endl;
    out << "vals size: " << (*vals)[2]<< endl;
    out << "vals size: " << (*vals)[3]<< endl;

    out << "val1 size: " << (*val1)[0]<< endl;

    ui->customPlot->legend->setVisible(true);
    ui->customPlot->legend->setFont(QFont("Helvetica", 9));
    QPen pen;

    int i = 0;
    ui->customPlot->addGraph();
    pen.setColor(QColor(qSin(i*1+1.2)*80+80, qSin(i*0.3+0)*80+80, qSin(i*0.3+1.5)*80+80));
    ui->customPlot->graph()->setPen(pen);
    ui->customPlot->graph()->setName("lsLine");
    ui->customPlot->graph()->setLineStyle(QCPGraph::lsLine);
    ui->customPlot->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));

    // Generate data
    QVector<double> x(15), y(15);
    for (int j = 0; j < 15; ++j)
    {
        x[j] = j + 1;
        y[j] = j + 2;
//        x[j] = (*vals)[1] + j;
//        y[j] = (*vals)[2] + j;
    }
    ui->customPlot->graph()->setData(x, y);

    // zoom out a bit:
    ui->customPlot->yAxis->scaleRange(1.1, ui->customPlot->yAxis->range().center());
    ui->customPlot->xAxis->scaleRange(1.1, ui->customPlot->xAxis->range().center());
    // set blank axis lines:
    ui->customPlot->xAxis->setTicks(false);
    ui->customPlot->yAxis->setTicks(true);
    ui->customPlot->xAxis->setTickLabels(false);
    ui->customPlot->yAxis->setTickLabels(true);
    // make top right axes clones of bottom left axes:
    ui->customPlot->axisRect()->setupFullAxesBox();

//    // Generate data
//    QVector<double> x(101), y(101); //Init with entries 0.100
//    for(int i = 0; i < 101; ++i)
//    {
//        x[i] = i/50.0 - 1; // x goes from -1 to 1
//        y[i] = x[i] * x[i]; // Quadratic function
//    }

//    QVector<QCPScatterStyle::ScatterShape> shapes;
//    shapes << QCPScatterStyle::ssCross;
//    shapes << QCPScatterStyle::ssPlus;
//    shapes << QCPScatterStyle::ssDisc;



//    ui->customPlot->legend->setVisible(true);
//    ui->customPlot->legend->setFont(QFont("Helvetica", 9));
//    ui->customPlot->legend->setRowSpacing(-3);

//    // Create graph & assign data to it
//    ui->customPlot->addGraph();
//    ui->customPlot->graph(0)->setData(x, y);

//    //Give the axes some labels:
//    ui->customPlot->xAxis->setLabel("x");
//    ui->customPlot->yAxis->setLabel("y");

//    //set axes ranges so we see all data
//    ui->customPlot->xAxis->setRange(-1, 1);
//    ui->customPlot->yAxis->setRange(0, 1);
//    ui->customPlot->replot();
}

Mission* GraphWidget::getNewMission(){
    Mission *newMission = new Mission();


    Protocol::TelemetryPacket tp;
    tp.SetOrientation(1, 2, 3);
    tp.SetHeading(20);
    tp.SetVelocity(15, 16, 17);
    tp.SetLocation(10,10,40);

    newMission->addPacket(tp);

    return newMission;
}
