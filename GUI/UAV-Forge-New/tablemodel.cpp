#include "tablemodel.h"

TableModel::TableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
    columns.push_back("Action");
    columns.push_back("Longitude (X)");
    columns.push_back("E/W");
    columns.push_back("Latitude (Y)");
    columns.push_back("N/S");
    columns.push_back("Behavior");

}

TableModel::TableModel(QList<QList<QString> > pairs, QObject *parent)
    : QAbstractTableModel(parent)
{
    listOfPairs = pairs;
}

int TableModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return listOfPairs.size();
}

int TableModel::columnCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return columns.length();
}

QVariant TableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= listOfPairs.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        QList<QString> pair = listOfPairs.at(index.row());

        return pair.value(index.column());
    }
    return QVariant();
}

QVariant TableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        if (section < columnCount(QModelIndex()) && section >= 0) {
            return columns[section];
        }
    }
    return QVariant();
}

bool TableModel::insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginInsertRows(index, position, position + rows - 1);

    for (int row = 0; row < rows; ++row) {
        QList<QString> pair;
        listOfPairs.insert(position, pair);
    }

    endInsertRows();
    return true;
}

bool TableModel::insertRow(const QModelIndex &index)
{
    Q_UNUSED(index);
    int insertRow = rowCount(index);
    beginInsertRows(index, insertRow, insertRow);
    QList<QString> list;
    for (int i = 0; i < columnCount(QModelIndex()); i++) {
        list << "";
    }
    listOfPairs.push_back(list);
    endInsertRows();
    return true;
}



bool TableModel::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginRemoveRows(index, position, position + rows - 1);

    for (int row = 0; row < rows; ++row) {
        listOfPairs.removeAt(position);
    }

    endRemoveRows();
    return true;
}

bool TableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        int row = index.row();

        QList<QString> p = listOfPairs.value(row);
        p[index.column()] = value.toString();
        listOfPairs.replace(row, p);
        emit(dataChanged(index, index));

        return true;
    }

    return false;
}

Qt::ItemFlags TableModel::flags(const QModelIndex &index) const
{
    if (!index.isValid())
        return Qt::ItemIsEnabled;

    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

QList< QList<QString> > TableModel::getList()
{
    return listOfPairs;
}

bool TableModel::removeRows(QModelIndexList indexes) {
    beginResetModel();
    qSort(indexes);
    for(int i = indexes.size() - 1; i >= 0 ; i--) {
        listOfPairs.removeAt(indexes.at(i).row());
    }
    endResetModel();
    return true;
}
