#ifndef MAPEXECUTION_H
#define MAPEXECUTION_H

#include <QWidget>
#include "gsclient.h"
#include "gsserver.h"

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
};

#endif // MAPEXECUTION_H
