/* This is the header file for the MapExecution class. For information about
 * this class and its functions, see comments on the top of mapexecution.cpp.
 *
 * File added sometime prior to April 30 2015.
 */
#ifndef MapExecution_H
#define MapExecution_H

#include <QWidget>
#include "gsclient.h"
#include "gsserver.h"

namespace Ui {
class MapExecution;
}

class MapExecution : public QWidget
{
    Q_OBJECT
public:
    //Constructor for a blank mission execution map
    explicit MapExecution(QWidget *parent = 0);

    //Constructor for an execution map with a flightpath defined by strings
    //  strings - This is a list of strings each formatted (Action,Lat,
    //          LatDir,Lng,LngDir,Behavior). These strings are used to
    //          create the flightpath that is drawn in the view window.
    explicit MapExecution(QList<QString> strings, QWidget *parent = 0);

    //Destructor
    ~MapExecution();

    //mapStrings - contains the list of strings this object is ceated with
    QList<QString> mapStrings;

    //myServer - used to recieve data from the UAV
    GsServer myServer;

    //myClient - used to send data to the UAV
    GsClient myClient;

    //flightPath - a list of <lat,lng> points recived since the start of the
    //          mission from the UAV. These are the points of the red line.
    QList<QPair<double, double> > flightPath;

    //getDoublePairs - extracts lat and lng values from a list of strings
    //          each formatted (Action,Lat,LatDir,Lng,LngDir,Behavior)
    //  strings - the list of strings from which values will be extracted
    QList<QPair<double, double> > getDoublePairs(QList<QString> strings);

public slots:
    //addNewMap - called in the JavaScript program to load the map described by
    //          mapStrings only after the JavaScript page has loaded fully
    void addNewMap();

    //setMap - used to draw a flight path on the display map
    //  list - the list of strings that determine the flight path drawn
    void setMap(QList<QString> list);

    //plotPosition - used to plot telemetry points (the red line) that are
    //          recieved from the quadcopter
    //  lat - the latitude value
    //  lng - the longitude value
    void plotPosition(double lat, double lng);

private:
    //addPoint - used to add a single point to the planned flight path (the
    //          blue line)
    //  string -  a string formatted (Action,Lat,LatDir,Lng,LngDir,Behavior)
    //          from which the doubles Lat and Lng are extracted
    void addPoint(QString string);

    //Ui object used to display the window
    Ui::MapExecution *ui;

private slots:
    //addClickListener - used to recreate the JavaScript/C++ bridge on reloads
    void addClickListener();

    //button commands
    void finishClicked();
    void returnHomeClicked();
    void cancelClicked();
    void stopClicked();
    void on_pushButton_clicked();
};

#endif // MapExecution_H
