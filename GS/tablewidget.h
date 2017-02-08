#ifndef TABLEWIDGET_H
#define TABLEWIDGET_H

#include <QWidget>
#include <QTableView>
#include "qcomboboxdelegate.h"
#include "tablemodel.h"

class TableWidget : public QTableView
{
    Q_OBJECT
public:
    /// Standard QWidget constructor and destructor.
    explicit TableWidget(QWidget *parent = 0);
    ~TableWidget();

    /**
     * @brief getModel
     * @return A pointer to this object's TableModel object.
     */
    TableModel* getModel();

private:
    /**
     * @brief model
     */
    TableModel model;

    /**
     * @brief delegate
     */
    QComboBoxDelegate delegate;

signals:
    /**
     * @brief tableUpdated
     */
    void tableUpdated();

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
};

#endif // TABLEWIDGET_H
