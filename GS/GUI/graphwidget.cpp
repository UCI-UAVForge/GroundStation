#include "graphwidget.h"
#include "ui_graphwidget.h"
#include <QTextStream> //For debugging
#include <QDebug>

GraphWidget::GraphWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GraphWidget)
{
    // Set up graphName
    QString graphName[10] = {"Heading", "Latitude", "Longtitude", "Altitude", "Pitch", "Roll",
                "Yaw", "Xvel", "Yvel", "Zvel"};

    ui->setupUi(this);
    firstEntry = 0;
    maxEntries = 2000;

    //ui->setupUi(this);
    this->setGeometry(0,0,400,400);
    checkboxes[0] = ui->btn_heading;
    checkboxes[1] = ui->btn_lat;
    checkboxes[2] = ui->btn_lon;
    checkboxes[3] = ui->btn_alt;
    checkboxes[4] = ui->btn_pitch;
    checkboxes[5] = ui->btn_roll;
    checkboxes[6] = ui->btn_yaw;
    checkboxes[7] = ui->btn_xvel;
    checkboxes[8] = ui->btn_yvel;
    checkboxes[9] = ui->btn_zvel;

    for(int i = 0; i < 10; i++){
        graphs[i] = ui->customPlot->addGraph();
        //graphs[i] = new QCPGraph(ui->customPlot->xAxis,ui->customPlot->yAxis);
        QPen pen;
        pen.setColor(QColor(qSin(i+1.2)*80+80, qSin(i*0.3)*80+80, qSin(i*0.3+1.5)*80+80));
        graphs[i]->setPen(pen);
        graphs[i]->setLineStyle(QCPGraph::lsLine);
        graphs[i]->setName(graphName[i]);

        //graphs[i]->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));
        graphs[i]->setVisible(false);
        graphs[i]->removeFromLegend();
    }

    // set blank axis lines:
    ui->customPlot->xAxis->setTicks(false);
    ui->customPlot->yAxis->setTicks(true);
    ui->customPlot->xAxis->setTickLabels(false);
    ui->customPlot->yAxis->setTickLabels(true);
    // make top right axes clones of bottom left axes:
    ui->customPlot->axisRect()->setupFullAxesBox();

    ui->customPlot->legend->setVisible(true);
    ui->customPlot->legend->setFont(QFont("Helvetica", 9));
}

GraphWidget::~GraphWidget()
{
    delete ui;
}

void GraphWidget::setMaxEntries(unsigned int numberOfEntries){
    maxEntries = numberOfEntries;
}

void GraphWidget::setViewport(unsigned int start, unsigned int end){
    if(start > end){
        qDebug() << "Reversed viewports are currently unsupported. Swapping 'start' and 'end'";
        int temp = start;
        start = end;
        end = temp;
    }
    firstEntry = start;
    maxEntries = end - start;
}

void GraphWidget::appendTelemData(mavlink_gps_raw_int_t msg) {
    int time = 0;
    if(graphs[0]->data()->size() > 0){
        time = graphs[0]->data()->lastKey()+1;
    }

    if(graphs[0]->data()->size() > maxEntries){
        for(int i = 0; i < 10; i++){
            graphs[i]->removeDataBefore(time-maxEntries);
        }
    }
    //qDebug() << time;
    graphs[0]->removeDataBefore(time-20);
    graphs[1]->removeDataBefore(time-20);
    graphs[2]->removeDataBefore(time-20);
    graphs[3]->removeDataBefore(time-20);
    graphs[0]->addData(time,msg.epv);
    graphs[1]->addData(time,msg.lat/1000000);
    graphs[2]->addData(time,(float)msg.lon/1000000);
    graphs[3]->addData(time,(float)msg.alt/1000);
   // graphs[4]->addData(time,data->pitch);
   // graphs[5]->addData(time,data->roll);
   // graphs[6]->addData(time,data->yaw);
   // graphs[7]->addData(time,data->xvel);
   // graphs[8]->addData(time,data->yvel);
   // graphs[9]->addData(time,data->zvel);

    updateGraph();
}

void GraphWidget::appendPoint(double x, double y, int id) {
    graphs[id]->addData(x,y);
}

void GraphWidget::drawMission(Mission* mission){
    myMission = mission;
    for(int i = 0; i < 10; i++){
        QCPGraph *graph = graphs[i];
        QVector<double> * vals = mission->getValuesForID(i);
        for (int j = 0; j < vals->length(); ++j) {
            graph->addData(j,(*vals)[j]);
        }
        processClickEvent(i);
    }

}

void GraphWidget::updateGraph(){
    // zoom out a bit:
    ui->customPlot->yAxis->rescale(true);
    ui->customPlot->xAxis->rescale(true);

    // make top right axes clones of bottom left axes:
    ui->customPlot->axisRect()->setupFullAxesBox();
    ui->customPlot->replot(); // Redraw graph
}

void GraphWidget::processClickEvent(int index) {
    if (checkboxes[index]->isChecked())
    {
        graphs[index]->setVisible(true);
        graphs[index]->addToLegend();
    }
    else
    {
        graphs[index]->setVisible(false);
        graphs[index]->removeFromLegend();
    }
    updateGraph();
}

void GraphWidget::on_btn_heading_clicked(){
    processClickEvent(0);
}

void GraphWidget::on_btn_lat_clicked(){
    processClickEvent(1);
}

void GraphWidget::on_btn_lon_clicked(){
    processClickEvent(2);
}

void GraphWidget::on_btn_alt_clicked(){
    processClickEvent(3);
}

void GraphWidget::on_btn_pitch_clicked(){
    processClickEvent(4);
}

void GraphWidget::on_btn_roll_clicked(){
    processClickEvent(5);
}

void GraphWidget::on_btn_yaw_clicked(){
    processClickEvent(6);
}

void GraphWidget::on_btn_xvel_clicked() {
    processClickEvent(7);
}

void GraphWidget::on_btn_yvel_clicked(){
    processClickEvent(8);
}

void GraphWidget::on_btn_zvel_clicked(){
    processClickEvent(9);
}
