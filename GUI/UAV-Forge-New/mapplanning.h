/* For more information about the MapPlanning class and its functions, see
 * the comments in MapPlanning.cpp file.
 *
 * File added sometime prior to April 30 2015.
 */

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
    void updateMap();
    QList<QString> getTableAsStrings();

public slots:
    //addPointToTable - used to add an entry with latitude lat and longitude lng to the table.
    //  lat - the latitude value (usually from the JavaScript program).
    //  lng - the longitude value (usually from the JavaScript program).
    void addPointToTable(double lat, double lng);

private slots:
    //button action slots
    void on_back_clicked();
    void on_addRow_clicked();
    void on_removeRow_clicked();
    void on_execute_clicked();
    void on_update_clicked();
    void on_clearPath_clicked();

    //addClickListener - Slot mapped to javaScriptWindowObjectCleared() from ui->webView->page()->mainFrame()
    void addClickListener();

    //closeWindow - Slot used by popupWindowMP to close this window once Mission Execution starts
    void closeWindow();

    QList<QList<QString> > getTableData();


private:
    Ui::MapPlanning *ui;
    QButtonGroup *buttonGroup;
    QPushButton *del;
    TableModel *model;
    PopWindowMP *popup;
};

#endif // MAPPLANNING_H
