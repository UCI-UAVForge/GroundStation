#include "tablewidget.h"
#include "qcomboboxdelegate.h"
#include <iostream>
#include <QDebug>

TableWidget::TableWidget(QWidget *parent) : QTableView(parent) {
    setModel(&model);
    setItemDelegate(&delegate);
    setSelectionBehavior(QAbstractItemView::SelectRows);
}

TableWidget::~TableWidget(){
    //QTableView::~QTableView();
}


void TableWidget::removeSelectedRows(){
    QModelIndexList indexes = this->selectionModel()->selectedIndexes();
    model.removeRows(indexes);
    emit tableUpdated();
}

void TableWidget::clearTable(){
    qDebug()<< "DELETING";
    while(model.rowCount(model.index(0,0)) > 0){
        model.removeRow(0);
    }
    qDebug()<< "DELETED";
    emit tableUpdated();
}

/// \todo look for optimizations here now that we can access all of the table
/// methods -Jordan


void TableWidget::setEditable(bool editable) {
    this->editable = editable;
    this->setEnabled(editable);
}

bool TableWidget::isEditable(){
    return editable;
}

void TableWidget::insertMissionTelem(Mission* mission) {
    for(int i = 0; i < mission->numOfEntries(); i++){
        double lat = mission->getValueForIndexAndID(i,1);
        double lng = mission->getValueForIndexAndID(i,2);

    }
}

