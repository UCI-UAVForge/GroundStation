#include "missiontable.h"
#include <QDebug>

MissionTable::MissionTable(QWidget *parent) : QTableView(parent)
{
    setSelectionBehavior(QAbstractItemView::SelectRows);
    setSelectionMode(QAbstractItemView::SingleSelection);
    horizontalHeader()->show();

}

void MissionTable::setTableModel(QStandardItemModel * model) {
    setModel(model);
    horizontalHeader()->setSectionResizeMode(0, QHeaderView::Stretch);
    for (int c = 1; c < horizontalHeader()->count(); ++c) {
        horizontalHeader()->setSectionResizeMode(
            c, QHeaderView::ResizeToContents);
    }
    connect(selectionModel(), &QItemSelectionModel::selectionChanged,
                this, &MissionTable::selectChanged);
}


void MissionTable::selectChanged(const QItemSelection & selected, const QItemSelection & deselected) {
    current = selected.indexes().at(0).row();
    emit(selectWaypoint(selected.indexes().at(0).row()));
    qDebug() << current;
}


void MissionTable::keyPressEvent( QKeyEvent *k ) {
    int selectedRow = selectionModel()->selectedRows(0).at(0).row();
    if (k->key() == Qt::Key_Tab) {
        int nextRow = selectedRow + 1;
        if (nextRow >= model()->rowCount()) {
            nextRow = 0;
        }
        selectionModel()->select(model()->index(nextRow, 0),
                                 QItemSelectionModel::ClearAndSelect|QItemSelectionModel::Rows );
    }
    emit(moveWaypoint(current, k->key()));
}
