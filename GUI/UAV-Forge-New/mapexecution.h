#ifndef MAPEXECUTION_H
#define MAPEXECUTION_H

#include <QWidget>

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
    ~mapexecution();
private slots:
    void finishClicked();
    void returnHomeClicked();
    void cancelClicked();
    void on_pushButton_clicked();

    void push_new_point(QString point);

    void addClickListener();
    //addClickListener - Slot mapped to javaScriptWindowObjectCleared() from ui->webView->page()->mainFrame().

private:
    Ui::mapexecution *ui;
    QList<QString> points_recieved;
};

#endif // MAPEXECUTION_H
