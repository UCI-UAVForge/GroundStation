#include "tablewidget.h"
#include "qcomboboxdelegate.h"
#include <iostream>
#include <QDebug>

TableWidget::TableWidget(QWidget *parent) : QTableView(parent) {
    setModel(&model);
    setItemDelegate(&delegate);
    setSelectionBehavior(QAbstractItemView::SelectRows);
    this->connect(this->selectionModel(), &QItemSelectionModel::selectionChanged, this, &TableWidget::getSelectedData);
}

TableWidget::~TableWidget(){
    //QTableView::~QTableView();
}

void TableWidget::appendRow(double lat, double lng){
    model.insertRow(lng,lat);
    this->scrollToBottom();
}
void TableWidget::getSelectedData(){
    QItemSelectionModel *m = this->selectionModel();
    QModelIndexList indexes = m->selectedIndexes();
    FlightPath * fp = new FlightPath();
    QVector<Protocol::Waypoint> latlngs;
    for (int i = 1; i < indexes.count(); i += 8) {
        Protocol::Waypoint wp;
        int dirlng = (m->model()->data(indexes[i+1]).toString() == "E")?1:-1;
        int dirlat = (m->model()->data(indexes[i+3]).toString() == "N")?1:-1;
        wp.lat = (m->model()->data(indexes[i+2]).toDouble())* dirlat;
        wp.lon = (m->model()->data(indexes[i]).toDouble())* dirlng;
        fp->addNavAction(wp, 0);
    }
    emit selectedData(fp, -1);
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

/// \todo look for optimizations here now that we can access all of the table
/// methods -Jordan
FlightPath* TableWidget::getTableAsFlightPath(){
    FlightPath *newFP = new FlightPath();
    QList<QList<QString> > table = model.getList();
    for(int i = 0; i < table.length(); i++) {
        QList<QString> row = table[i];
        Protocol::Waypoint wp;
        wp.lon = row[1].toDouble();
        wp.lon *= (row[2].at(0)=='E')?1:-1;

        wp.lat = row[3].toDouble();
        wp.lat *= (row[4].at(0)=='N')?1:-1;

        wp.alt = row[5].toDouble();

        wp.speed = row[6].toDouble();

        newFP->addNavAction(wp,i*10);
    }

    return newFP;
}
