#ifndef MAPEXECUTION_H
#define MAPEXECUTION_H

#include <QWidget>
#include <QDialog>
#include <QComboBox>
#include <QPushButton>
#include <QButtonGroup>
#include <QWebFrame>
#include <QPair>
#include <QList>

#include "digitalclock.h"
#include "gsserver.h"
#include "tablemodel.h"
#include "qcomboboxdelegate.h"
#include "missionrecap.h"
#include "options.h"
#include "messagebox.h"

#include "ui_mapexecution.h"
#include "messagebox.h"
#include "connectiondialog.h"

#include "flightpath.h"


namespace Ui {
class MapExecution;
}

class MapExecution : public QDialog {
    Q_OBJECT
public slots:
    void addNewMap();
    void plotPosition(double lat, double lng);
    void sendCoordToJSMap(double lat, double lng, int mapID);
    void drawFlightPath(FlightPath *flightPath);
    void updateTable(double lat, double lng);
    void sendFlightPlan();
    void updateStatusIndicator();

public:
    MapExecution(FlightPath* flightPath, QWidget *parent = 0);
    explicit MapExecution(QWidget *parent = 0);
    ~MapExecution();

    GsServer myServer;
    messagebox MyMessageBox;
    messagebox MessageBox;

private slots:
    void on_finishButton_clicked();
    void on_returnHomeButton_clicked();
    void on_cancelButton_clicked();
    void on_stopButton_clicked();
    void on_backButton_clicked();

    void addClickListener();

private:
    Ui::MapExecution *ui;
    TableModel *model;
    QButtonGroup *buttonGroup;
    double prevLat, prevLng, prevAlt;
    QTime prevTime;

    FlightPath *myFlightPath;

    bool missionStarted;
};

#endif // MAPEXECUTION_H
