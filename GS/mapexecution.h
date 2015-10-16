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
    void addPoint(QString string);
    void addNewMap();
    void updateTable(int lat, int lng);
public:
    explicit MapExecution(QList<QString> strings, QWidget *parent = 0);
    explicit MapExecution(QWidget *parent = 0);
    QList<QString> mapStrings;
    void plotPosition(double lat, double lng);
    ~MapExecution();
    //GsServer myServer;
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


private:
    Ui::MapExecution *ui;
    QList<QString> points_recieved;
    TableModel *model;
    QButtonGroup *buttonGroup;
};

#endif // MAPEXECUTION_H
