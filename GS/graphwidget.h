#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QWidget>

#include <qcustomplot.h>

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

    Mission* getNewMission();

    QCPGraph* makePlot(int index);
    void processClickEvent(QCheckBox* checkbox, QCPGraph** graph, int index);

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
};

#endif // GRAPHWIDGET_H
