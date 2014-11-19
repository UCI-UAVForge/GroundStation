#include "tablemodel.h"

TableModel::TableModel(QObject *parent)
    : QAbstractTableModel(parent)
{
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
    return 3;
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
        switch (section) {
        case 0:
            return tr("Action");
        case 1:
            return tr("Lattitude");
        case 2:
            return tr("Lattitude Direction");
        case 3:
            return tr("Longitude");
        case 4:
            return tr("Longitude Direction");
        case 5:
            return tr("Behavior");
        default:
            return QVariant();
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
    list << "" << "" << "";
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
