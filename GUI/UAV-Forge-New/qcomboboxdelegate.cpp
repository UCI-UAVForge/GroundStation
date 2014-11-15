#include "qcomboboxdelegate.h"

QComboBoxDelegate::QComboBoxDelegate(QObject *parent) :
    QItemDelegate(parent)
{
}

QWidget* QComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    return new QWidget();
}

void QComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {

}

void QComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {

}

void QComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    editor->setGeometry(option.rect);
}
