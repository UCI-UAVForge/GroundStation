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

#include "gsclient.h"
#include "gsserver.h"
#include "tablemodel.h"
#include "qcomboboxdelegate.h"
#include "missionrecap.h"
#include "options.h"
//#include "mainwindow.h"
//#include "net.h"

#include "ui_mapexecution.h"


namespace Ui {
class MapExecution;
}

class MapExecution : public QDialog {
    Q_OBJECT
public slots:
    void setMap(QList<QString> list);
    void addNewMap();
  
    void updateTable(double lat, double lng);
    void newTelemCoord(QString coordString);
    void sendFlightPlan();
    void updatePosition(double lat, double lng, double alt, double spd);
public:
    explicit MapExecution(QList<QString> strings, QWidget *parent = 0);
    explicit MapExecution(QWidget *parent = 0);
    void plotPosition(double lat, double lng);
    ~MapExecution();
    GsServer myServer;
    GsClient myClient;
    QList<QPair<double,double> > getDoublePairs(QList<QString> strings);
private slots:
    void on_finishButton_clicked();
    void on_returnHomeButton_clicked();
    void on_cancelButton_clicked();
    void on_stopButton_clicked();
    void on_backButton_clicked();

    void push_new_point(QString point);

    void addClickListener();
    //addClickListener - Slot mapped to javaScriptWindowObjectCleared() from ui->webView->page()->mainFrame().
    void initCurrentData();

    void updateStatusIndicator(int x);
    void on_colorTester_clicked();

private:
    void addPoint(QString string);
    QList<QString> mapStrings;
    Ui::MapExecution *ui;
    QList<QString> points_recieved;
    TableModel *model;
    QButtonGroup *buttonGroup;
    double prevLat, prevLng, prevAlt;
    QTime prevTime;
    QTableWidget *CurrentData;
    QTableWidgetItem *LatLabel, *LngLabel, *AltLabel, *SpdLabel;
};

#endif // MAPEXECUTION_H
