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

public slots:
    //addPointToTable - used to add an entry with latitude lat and longitude
    //          lng to the table. (usually called on the JavaScript side)
    //  lat - the GPS latitude value
    //  lng - the GPS longitude value
    void addPointToTable(double lat, double lng);

private slots:
    //button actions
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

private:
    void updateMap();
    //getTableAsStrings - Used to extract data from the table and store as a
    //          list of strings.
    //  returns a list of strings each fromatted (Action,Lng,LngDir,Lat,LatDir,
    //          Behavior). Example: "Action 1,113.5,W,35.2,N,Behavior 1"
    QList<QString> getTableAsStrings();

    //getTableData - Used to extract data from the table and store as a list of
    //          lists of strings. Very similar to getTableAsStrings
    //  returns a list of lists of strings each fromatted {(Action), (Lng),
    //          (LngDir), (Lat), (LatDir), (Behavior)}.
    //          Example: ["Action 1", "113.5", W", "35.2", "Behavior 1"]
    QList<QList<QString> > getTableData();

    //ui - UI object used to do the window layout
    Ui::MapPlanning *ui;

    //model - table object used to format the table and store its values
    TableModel *model;

    //These were unused I'll delete them later -Jordan
    //QButtonGroup *buttonGroup;
    //QPushButton *del;
    //PopWindowMP *popup;
};

#endif // MAPPLANNING_H
