#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QWidget>
#include <QVector>
#include "qcustomplot.h"
#include "mission.h"

namespace Ui {
class GraphWidget;
}

class GraphWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GraphWidget(QWidget *parent = 0);
    ~GraphWidget();

public slots:
    void appendPoint(double x, double y, int id);
    void drawMission(Mission* mission);
    void appendTelemPacket(Protocol::TelemetryPacket* packet);


private slots:
    void on_btn_heading_clicked();

    void on_btn_lat_clicked();

    void on_btn_lon_clicked();

    void on_btn_alt_clicked();

    void on_btn_pitch_clicked();

    void on_btn_roll_clicked();

    void on_btn_yaw_clicked();

    void on_btn_xvel_clicked();

    void on_btn_yvel_clicked();

    void on_btn_zvel_clicked();

private:
    Ui::GraphWidget *ui;

    /**
     * @brief data A 2d vector of the form data[id][index]. id specifies the graph that
     * the datapoint belongs to. index specifies the index of the datapoint.
     */
    QVector<QVector<double>> data;

    Mission* getNewMission();
    Mission *myMission;

    void makePlot(int index);
    void processClickEvent(int index);

    QCheckBox* checkboxes[10];
    QCPGraph* graphs[10];

    QCPGraph* graph_heading;
    QCPGraph* graph_lat;
    QCPGraph* graph_lon;
    QCPGraph* graph_alt;
    QCPGraph* graph_pitch;
    QCPGraph* graph_roll;
    QCPGraph* graph_yaw;
    QCPGraph* graph_xvel;
    QCPGraph* graph_yvel;
    QCPGraph* graph_zvel;
    void updateGraph();
//    QString graphName[10];
};

#endif // GRAPHWIDGET_H
