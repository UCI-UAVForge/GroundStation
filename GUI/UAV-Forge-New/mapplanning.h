#ifndef MAPPLANNING_H
#define MAPPLANNING_H

#include <QDialog>
#include <QComboBox>
#include <QPushButton>
#include <QButtonGroup>
#include <QWebFrame>
#include "tablemodel.h"
#include "popwindowmp.h"
#include "qcomboboxdelegate.h"

namespace Ui {
class MapPlanning;
}

class MapPlanning : public QDialog
{
    Q_OBJECT

public:
    explicit MapPlanning(QWidget *parent = 0);
    ~MapPlanning();

private slots:
    void on_pushButton_6_clicked();
    void on_pushButton_5_clicked();
    //void buttonWasClicked(int);
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();

    void on_pushButton_clicked();

    void on_clearTable_clicked();

    void on_clearMap_clicked();

private:
    Ui::MapPlanning *ui;
    QButtonGroup *buttonGroup;
    QPushButton *del;
    TableModel *model;
    PopWindowMP *popup;
};

#endif // MAPPLANNING_H
