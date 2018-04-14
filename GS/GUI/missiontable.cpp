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
    if (selected.indexes().length() > 0) {
        current = selected.indexes().at(0).row();
        emit(selectWaypoint(current));
    }
}

void MissionTable::focusInEvent(QFocusEvent* e) {
    emit(editMode(true));
}
void MissionTable::focusOutEvent(QFocusEvent *event) {
    selectionModel()->clearSelection();
    emit(editMode(false));
}


void MissionTable::keyPressEvent( QKeyEvent *k ) {
    if (selectionModel()->selectedRows(0).length() > 0) {
        if (k->key() == Qt::Key_Tab) {
            int selectedRow = selectionModel()->selectedRows(0).at(0).row();
            int nextRow = selectedRow + 1;
            if (nextRow >= model()->rowCount()) {
                nextRow = 0;
            }
            selectionModel()->select(model()->index(nextRow, 0),
                                     QItemSelectionModel::ClearAndSelect|QItemSelectionModel::Rows );
        }
        if (k->key() == Qt::Key_A) {
            emit(addWaypoint(current));
            return;
        }
        if (k->key() == Qt::Key_R) {
            emit(removeWaypoint(current));
            return;
        }
        emit(moveWaypoint(current, k->key()));
    }
}
