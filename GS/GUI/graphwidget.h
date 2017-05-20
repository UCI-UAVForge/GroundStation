#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include <QWidget>
#include <QVector>
#include "qcustomplot.h"
#include "mission.h"
#include "dataobjects.h"

namespace Ui {
class GraphWidget;
}

/**
 * @brief The GraphWidget class defines a GUI Widget that allows for the
 * tracing of multiple datastreams on a single graph window.
 * @author Duy Nguyen
 * @author Jordan Dickson
 */
class GraphWidget : public QWidget
{
    Q_OBJECT

public:
    explicit GraphWidget(QWidget *parent = 0);
    ~GraphWidget();

public slots:
    /**
     * @brief appendPoint Appends the point (x,y) to the trace with the
     * specified id.
     * @param x the distance along the x axis (usually time)
     * @param y the distance along the y axis (usually the value)
     * @param id the id of the trace that will be appended to
     */
    void appendPoint(double x, double y, int id);

    /**
     * @brief drawMission Takes in a mission object, extracts all of its
     * data points, and appends each of those points to the correct trace.
     * @param mission pointer to a Mission object that will be drawn
     */
    void drawMission(Mission* mission);

    /**
     * @brief appendTelemPacket Takes a single telemetry packet and appends
     * each of its vaules to the correct trace on the graph
     * @param packet pointer to the packet that will be appended
     */
    void appendTelemPacket(Protocol::TelemetryPacket* packet);

    /**
     * @brief setMaxEntries Sets the maximum number of entries allowed in the
     * GraphWidget's viewport. If this number is exceeded, the graph will begin
     * to 'scroll' to the right, following the most recent data points as they
     * are appened.
     * @param numberOfEntries the maximum number of entries
     * @warning The current version does not support increasing the maximum number
     * of entries showing.
     * @todo fix this someday
     */
    void setMaxEntries(unsigned int numberOfEntries);

    /**
     * @brief setViewport Sets the start and stop x values of the GraphWidget's
     * viewport. Values outside this range will be hidden from view.
     * @param start the first x value that will be shown
     * @param end the last x value that will be shown
     * @warning this function is not ready to be used for setting viewports or
     * zooming in on certain locations on the graph.
     * @todo implement this one day
     */
    void setViewport(unsigned int start, unsigned int end);

    /**
     * @brief appendTelemData
     * @param data
     */
    void appendTelemData(TelemetryData *data);


private slots:
    /// slots for each of the checkboxes on the GUI used for showing/hiding traces
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
    /**
     * @brief ui Auto-generated ui object
     */
    Ui::GraphWidget *ui;

    /**
     * @brief data A 2d vector of the form data[id][index]. id specifies the graph that
     * the datapoint belongs to. index specifies the index of the datapoint.
     */
    QVector<QVector<double>> data;

    /**
     * @brief myMission
     */
    Mission *myMission;

    /**
     * @brief makePlot
     * @param index
     * @deprecated
     */
    //void makePlot(int index);

    /**
     * @brief processClickEvent checks the status of the check box with the given index
     * each time this is called. If the box is checked, then the trace with the matching
     * index will be drawn, otherwise the trace will be hidden.
     * @param index
     */
    void processClickEvent(int index);

    /**
     * @brief firstEntry the index of the first entry that will be drawn
     */
    int firstEntry;

    /**
     * @brief maxEntries the number of entries that will be drawn after the first entry
     */
    int maxEntries;

    /**
     * @brief checkboxes provides a more convenient way to reference each of
     * the checkboxes
     */
    QCheckBox* checkboxes[10];

    /**
     * @brief graphs provides a more convenient way to reference each of the
     * graph objects (traces)
     */
    QCPGraph* graphs[10];

    /// graphs for each of the traces that will be drawn in this window
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

    /**
     * @brief updateGraph resizes the viewport for the graph to make data
     * viewing easier.
     */
    void updateGraph();
};

#endif // GRAPHWIDGET_H
