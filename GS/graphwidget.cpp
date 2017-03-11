#include "graphwidget.h"
#include "ui_graphwidget.h"
#include <QTextStream> //For debugging

#include "telemetrypacket.h"

GraphWidget::GraphWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GraphWidget)
{
    ui->setupUi(this);
//    GraphWidget::makePlot();

    // set blank axis lines:
    ui->customPlot->xAxis->setTicks(false);
    ui->customPlot->yAxis->setTicks(true);
    ui->customPlot->xAxis->setTickLabels(false);
    ui->customPlot->yAxis->setTickLabels(true);
    // make top right axes clones of bottom left axes:
    ui->customPlot->axisRect()->setupFullAxesBox();
}

GraphWidget::~GraphWidget()
{
    delete ui;
    delete graph_heading;
    delete graph_lat;
    delete graph_lon;
    delete graph_alt;
    delete graph_pitch;
    delete graph_roll;
    delete graph_yaw;
    delete graph_xvel;
    delete graph_yvel;
    delete graph_zvel;
}

QCPGraph* GraphWidget::makePlot(int index)
{
    QTextStream out(stdout);
    QCPGraph* graph = ui->customPlot->addGraph();
    // Create mission
    Mission* mission = getNewMission();

    QVector<double> * vals = mission->getValuesForID(1);

    // Get checkboxes value

    ui->customPlot->legend->setVisible(true);
    ui->customPlot->legend->setFont(QFont("Helvetica", 9));
    QPen pen;

    pen.setColor(QColor(qSin(index*1+1.2)*80+80, qSin(index*0.3+0)*80+80, qSin(index*0.3+1.5)*80+80));
    graph->setPen(pen);
    graph->setName("lsLine");
    graph->setLineStyle(QCPGraph::lsLine);
    graph->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));

    // Generate data
    QVector<double> x(15), y(15);
    for (int j = 0; j < 15; ++j)
    {
        x[j] = j;
        y[j] = qrand() % qCeil((*vals)[index]);

    }
    graph->setData(x, y);

    // zoom out a bit:
    ui->customPlot->yAxis->rescale();
    ui->customPlot->xAxis->rescale();

    // set blank axis lines:
    ui->customPlot->xAxis->setTicks(false);
    ui->customPlot->yAxis->setTicks(true);
    ui->customPlot->xAxis->setTickLabels(false);
    ui->customPlot->yAxis->setTickLabels(true);

    // make top right axes clones of bottom left axes:
    ui->customPlot->axisRect()->setupFullAxesBox();
    ui->customPlot->replot(); // Redraw graph
    return graph;
}

Mission* GraphWidget::getNewMission(){
    Mission *newMission = new Mission();

    for(int i = 0; i < 10; i++){
        Protocol::TelemetryPacket tp;
        tp.SetOrientation(1, 2, 3); // pitch, roll, yaw
        tp.SetHeading(20); // h
        tp.SetVelocity(15, 16, 17); // vX, vY, vZ
        tp.SetLocation(i,i,40); // lat, lon, alt

        newMission->addPacket(tp);
    }

    return newMission;
}

void GraphWidget::processClickEvent(QCheckBox* checkbox, QCPGraph** graph, int index)
{
    if (checkbox->isChecked())
    {
        *graph = makePlot(index);
    }
    else
    {
        ui->customPlot->removeGraph(*graph);
        ui->customPlot->replot(); // Redraw graph
    }
}

void GraphWidget::on_btn_heading_clicked()
{
    processClickEvent(ui->btn_heading, &graph_heading, 0);
}

void GraphWidget::on_btn_lat_clicked()
{
    processClickEvent(ui->btn_lat, &graph_lat, 1);
}


void GraphWidget::on_btn_lon_clicked()
{
    processClickEvent(ui->btn_lon, &graph_lon, 2);
}



void GraphWidget::on_btn_alt_clicked()
{
    processClickEvent(ui->btn_alt, &graph_alt, 3);
}



void GraphWidget::on_btn_pitch_clicked()
{
    processClickEvent(ui->btn_pitch, &graph_pitch, 4);
}


void GraphWidget::on_btn_roll_clicked()
{
    processClickEvent(ui->btn_roll, &graph_roll, 5);
}



void GraphWidget::on_btn_yaw_clicked()
{
    processClickEvent(ui->btn_yaw, &graph_yaw, 6);
}


void GraphWidget::on_btn_xvel_clicked()
{
    processClickEvent(ui->btn_xvel, &graph_xvel, 7);
}



void GraphWidget::on_btn_yvel_clicked()
{
    processClickEvent(ui->btn_yvel, &graph_yvel, 8);
}

void GraphWidget::on_btn_zvel_clicked()
{
    processClickEvent(ui->btn_zvel, &graph_zvel, 9);
}
