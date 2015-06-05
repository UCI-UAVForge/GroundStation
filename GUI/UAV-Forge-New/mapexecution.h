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
#include "mainwindow.h"
//#include "net.h"

#include "ui_mapexecution.h"


namespace Ui {
class mapexecution;
}

class mapexecution : public QWidget
{
    Q_OBJECT
public slots:
    void setMap(QList<QString> list);
    void addPoint(QString string);
    void addNewMap();
    void updateTable(int lat, int lng);
public:
    explicit mapexecution(QList<QString> strings, QWidget *parent = 0);
    explicit mapexecution(QWidget *parent = 0);
    QList<QString> mapStrings;
    void plotPosition(double lat, double lng);
    ~mapexecution();
    //GsServer myServer;
    GsClient myClient;
    QList<QPair<double,double> > getDoublePairs(QList<QString> strings);
private slots:
    void finishClicked();
    void returnHomeClicked();
    void cancelClicked();
    void stopClicked();
    void on_pushButton_clicked();

    void push_new_point(QString point);

    void addClickListener();
    //addClickListener - Slot mapped to javaScriptWindowObjectCleared() from ui->webView->page()->mainFrame().


private:
    Ui::mapexecution *ui;
    QList<QString> points_recieved;
    TableModel *model;
    QButtonGroup *buttonGroup;
};

#endif // MAPEXECUTION_H
