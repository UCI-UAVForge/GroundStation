#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QWidget>
#include <QTableView>
#include "qcomboboxdelegate.h"
#include "tablemodel.h"

#include "mission.h"

class TableWidget : public QTableView
{
    Q_OBJECT
public:
    /// Standard QWidget constructor and destructor.
    explicit TableWidget(QWidget *parent = 0);
    ~TableWidget();

    /**
     * @brief MapPlanning::getTableAsFlightPath
     * @return A pointer to a new FlightPath object based on the data
     * in the TableWidget. The FlightPath will contain the points in
     * the same (top-to-bottom) order as they appear in the table.
     */
    /**
     * @brief setEditable
     * @param editable - sets if the user can edit the table by hand or not
     */
    void setEditable(bool editable);

    /**
     * @brief isEditable
     * @return true if this table can be edited by the user
     */
    bool isEditable();

    /**
     * @brief insertMissionTelem
     * @param mission
     */
    void insertMissionTelem(Mission* mission);

    /**
     * @brief insertFlightPath
     * @param fp
     */

private:
    /**
     * @brief model - The TableModel we get our column names, types,
     * and validator from.
     */
    TableModel model;

    /**
     * @brief delegate - The QComboBoxDelegate used to control the
     * E/W and N/S drop-down menues embedded in the table.
     */
    QComboBoxDelegate delegate;

    /**
     * @brief editable
     */
    bool editable;

signals:
    /**
     * @brief tableUpdated
     */
    void tableUpdated();
    /**
     * @brief tablePathSent
     * @param fp
     * @param pathId
     */

public slots:
    /**
     * @brief appendRow
     * @param lat
     * @param lng
     */
    void appendRow(double lat, double lng);

    /**
     * @brief removeSelectedRows
     */
    void removeSelectedRows();


    /**
     * @brief clearTable
     */
    void clearTable();
    /**
     * @brief sendTableSelectionPath
     */
    void sendTableSelectionPath();
};

#endif // TABLEWIDGET_H
