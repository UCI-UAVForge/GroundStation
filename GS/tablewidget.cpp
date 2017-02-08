#include "tablewidget.h"
#include "qcomboboxdelegate.h"

TableWidget::TableWidget(QWidget *parent) : QTableView(parent) {
    setModel(&model);
    setItemDelegate(&delegate);
}

TableWidget::~TableWidget(){
    //QTableView::~QTableView();
}

TableModel* TableWidget::getModel(){
    return &model;
}

void TableWidget::appendRow(double lat, double lng){
    model.insertRow(lng,lat);
    this->scrollToBottom();
}

void TableWidget::removeSelectedRows(){
    QModelIndexList indexes = this->selectionModel()->selectedIndexes();
    model.removeRows(indexes);
    emit tableUpdated();
}

void TableWidget::clearTable(){
    while(model.rowCount(model.index(0,0)) > 0){
        model.removeRow(0);
    }
    emit tableUpdated();
}
