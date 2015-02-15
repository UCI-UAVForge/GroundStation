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
    void updateMap();
    explicit MapPlanning(QWidget *parent = 0);
    ~MapPlanning();

public slots:
    void addPointToTable(double lat, double lng);
    //addPointToTable - used to add an entry with latitude lat and longitude lng to the table.
    //  lat - the latitude value (usually from the JavaScript program).
    //  lng - the longitude value (usually from the JavaScript program).

private slots:
    void on_pushButton_6_clicked();
    void on_pushButton_5_clicked();
    void on_pushButton_7_clicked();
    void on_pushButton_8_clicked();
    void on_pushButton_clicked();

    void addClickListener();
    //addClickListener - Slot mapped to javaScriptWindowObjectCleared() from ui->webView->page()->mainFrame().

private:
    Ui::MapPlanning *ui;
    QButtonGroup *buttonGroup;
    QPushButton *del;
    TableModel *model;
    PopWindowMP *popup;
};

#endif // MAPPLANNING_H
