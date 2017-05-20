#ifndef MAPPLANNING_H
#define MAPPLANNING_H

#include <QDialog>
#include <QComboBox>
#include <QPushButton>
#include <QButtonGroup>
#include <QWebEngineView>
#include <QString>
#include <QApplication>
#include <QDoubleValidator>

#include "tablemodel.h"
#include "popwindowmp.h"
#include "qcomboboxdelegate.h"
#include "popwindowmp.h"
#include "flightpath.h"
#include "mapexecution.h"
#include "messagebox.h"
#include "mapwidget.h"

#include "ui_mapplanning.h"

namespace Ui {
    class MapPlanning;
}

class MapPlanning : public QDialog {
    Q_OBJECT
public:
    explicit MapPlanning(QWidget *parent = 0);
    ~MapPlanning();

    void updateMap();

    FlightPath* getTableAsFlightPath();

public slots:
    void addPointToTable(double lat, double lng);
    //addPointToTable - used to add an entry with latitude lat and longitude lng to the table.
    //  lat - the latitude value (usually from the JavaScript program).
    //  lng - the longitude value (usually from the JavaScript program).
    void clearTable();

    void setupMapPaths();

private slots:
    void on_executeButton_clicked();
    void on_addButton_clicked();
    void on_backButton_clicked();
    void on_deleteButton_clicked();
    void on_updateTableButton_clicked();

    void closeWindow();

private:
    Ui::MapPlanning *ui;

};

#endif // MAPPLANNING_H
