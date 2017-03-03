#include "graphwidget.h"
#include "ui_graphwidget.h"
#include <QTextStream> //For debugging

#include "telemetrypacket.h"

GraphWidget::GraphWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::GraphWidget)
{
    ui->setupUi(this);
    //GraphWidget::makePlot();
}

GraphWidget::~GraphWidget()
{
    delete ui;

}

void GraphWidget::appendPoint(double x, double y, int id) {
    //this->data.at(id).append(*x);
}

void GraphWidget::makePlot(int id) {
    // Create mission
    Mission* mission = getNewMission();


    QVector<double> * vals = mission->getValuesForID(1);
//    QVector<double> * val1 = mission->getValuesForID(6);

//    values.at(0)->append(heading);
//    values.at(1)->append(lat);
//    values.at(2)->append(lon);
//    values.at(3)->append(alt);
//    values.at(4)->append(pitch);
//    values.at(5)->append(roll);
//    values.at(6)->append(yaw);
//    values.at(7)->append(xvel);
//    values.at(8)->append(yvel);
//    values.at(9)->append(zvel);

    // Get checkboxes value


    // Test
    QTextStream out(stdout);
    out << "heading: " << (*vals)[0]<< endl;
    out << "lat: " << (*vals)[1]<< endl;
    out << "lon: " << (*vals)[2]<< endl;
    out << "alt: " << (*vals)[3]<< endl;

    ui->customPlot->legend->setVisible(true);
    ui->customPlot->legend->setFont(QFont("Helvetica", 9));
    QPen pen;
    QStringList lineNames;

    lineNames << "lsLine" << "lsStepLeft" << "lsStepRight" << "lsStepCenter" << "lsImpulse";


    int i = 0;
    ui->customPlot->addGraph();
    pen.setColor(QColor(qSin(i*1+1.2)*80+80, qSin(i*0.3+0)*80+80, qSin(i*0.3+1.5)*80+80));
    ui->customPlot->graph()->setPen(pen);
    ui->customPlot->graph()->setName("lsLine");
    ui->customPlot->graph()->setLineStyle(QCPGraph::lsLine);
    ui->customPlot->graph()->setScatterStyle(QCPScatterStyle(QCPScatterStyle::ssCircle, 5));

    // Generate data
    QVector<double> x(15);//, y(15);
    int max = 0;
    for (int j = 0; j < vals->length(); ++j)
    {
        x[j] = j;

        // Save max for scaling
        if (max > vals->at(j))
            max = vals->at(j);
        //out << "x" << i << ": " << x[j] << endl;
        //out << "y" << i << ": " << vals->at(j) << endl;
    }
    ui->customPlot->graph()->setData(x, *vals);

    // zoom out a bit:
//    ui->customPlot->yAxis->scaleRange(10, ui->customPlot->yAxis->range().center());
//    ui->customPlot->yAxis->scaleRange(2, max / 2);
    ui->customPlot->xAxis->scaleRange(10, 0);
    ui->customPlot->yAxis->rescale();

    // set blank axis lines:
    ui->customPlot->xAxis->setTicks(false);
    ui->customPlot->yAxis->setTicks(true);
    ui->customPlot->xAxis->setTickLabels(false);
    ui->customPlot->yAxis->setTickLabels(true);

    // make top right axes clones of bottom left axes:
    ui->customPlot->axisRect()->setupFullAxesBox();

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
