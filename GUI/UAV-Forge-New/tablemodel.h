#ifndef TABLEMODEL_H
#define TABLEMODEL_H

#include "tablemodel.h"
#include <QAbstractTableModel>
#include <QList>
#include <QPair>

class TableModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    TableModel(QObject *parent = 0);
    TableModel(QList<QList<QString> > listofPairs, QObject *parent = 0);

    int rowCount(const QModelIndex &parent) const;
    int columnCount(const QModelIndex &parent) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);
    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
    bool insertRow(const QModelIndex &index = QModelIndex());
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());
    QList<QList<QString> > getList();

private:
    QList<QList<QString> > listOfPairs;
};


#endif // TABLEMODEL_H
