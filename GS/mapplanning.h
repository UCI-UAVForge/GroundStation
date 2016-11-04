#ifndef MAPPLANNING_H
#define MAPPLANNING_H

#include <QDialog>
#include <QComboBox>
#include <QPushButton>
#include <QButtonGroup>
#include <QWebEnginePage>
#include <QWebFrame>
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

#include "ui_mapplanning.h"

namespace Ui {

    class MapPlanning;

}

class MapPlanning : public QDialog {

    Q_OBJECT

    /* Roman Parise - Maybe just make friend functions or something.
     * MainMDIDisplay is able to access private class variables of MapPlanning. */
    friend class MainMDIDisplay;

public:
    void updateMap();
    FlightPath *getTableAsFlightPath();
    explicit MapPlanning(QWidget *parent = 0);
    ~MapPlanning();

public slots:
    void addPointToTable(double lat, double lng);
    //addPointToTable - used to add an entry with latitude lat and longitude lng to the table.
    //  lat - the latitude value (usually from the JavaScript program).
    //  lng - the longitude value (usually from the JavaScript program).
    void clearTable();
private slots:
    void on_executeButton_clicked();
    void on_addButton_clicked();
    void on_backButton_clicked();
    void on_clearTableButton_clicked();
    void on_clearMapButton_clicked();
    void on_deleteButton_clicked();
    void on_updateTableButton_clicked();

    void addClickListener();
    //addClickListener - Slot mapped to javaScriptWindowObjectCleared() from ui->webView->page()->mainFrame().
    void closeWindow();

private:
    //Ui::MapPlanning *ui;
    QButtonGroup *buttonGroup;
    QPushButton *del;
    TableModel *model;
    PopWindowMP *popup;
    //QList<QList<QString> > tableData;

    Ui::MapPlanning *ui;

signals:

    /* Roman Parise - added to tell external classes and functions that we're ready to start map execution */
    void timeToStartMapExecution();

};

#endif // MAPPLANNING_H
