#include "qcomboboxdelegate.h"

QComboBoxDelegate::QComboBoxDelegate(QObject *parent) :
    QItemDelegate(parent)
{
}

QWidget* QComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const {

    if(index.column() == 1)
    {
        return QItemDelegate::createEditor(parent, option, index);
    }

    // Create the combobox and populate it
    QComboBox *comboBox = new QComboBox(parent);
    QString currentText = index.data(Qt::DisplayRole).toString();
    if (currentText != 0)
    {
        comboBox->addItem(currentText);
    }
    if (index.column() == 0)
    {
        comboBox->addItem(QString("Action 1"));
        comboBox->addItem(QString("Action 2"));
        comboBox->addItem(QString("Action 3"));
    }
    else {
        comboBox->addItem(QString("Behavior 1"));
        comboBox->addItem(QString("Behavior 2"));
        comboBox->addItem(QString("Behavior 3"));
    }
    return comboBox;
}

void QComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {

    if(QComboBox *comboBox = qobject_cast<QComboBox *>(editor)) {
        comboBox->showPopup();
        QString currentText = index.data(Qt::EditRole).toString();
        int comboBoxIndex = comboBox->findText(currentText);

        if(comboBoxIndex >= 0) {
            comboBox->setCurrentIndex(comboBoxIndex);
        }
    } else {
        QItemDelegate::setEditorData(editor, index);
    }
}

void QComboBoxDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
    if(QComboBox *cb = qobject_cast<QComboBox *>(editor))
    {
        model->setData(index, cb->currentText(), Qt::EditRole);
    }
    else
    {
        QItemDelegate::setModelData(editor, model, index);
    }
}

void QComboBoxDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &index) const {
    editor->setGeometry(option.rect);
}
