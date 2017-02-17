#include "qcomboboxdelegate.h"

QComboBoxDelegate::QComboBoxDelegate(QObject *parent) :
    QItemDelegate(parent)
{
}

QWidget* QComboBoxDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const {

    // Create the combobox and populate it
    QString currentText = index.data(Qt::DisplayRole).toString();
    if (index.column() == 0)
    {
        QComboBox *comboBox = new QComboBox(parent);
        comboBox->addItem(QString("Action 1"));
        comboBox->addItem(QString("Action 2"));
        comboBox->addItem(QString("Action 3"));
        return comboBox;
    }
    //This checks the validation for the Longitude input
    if(index.column() == 1)
    {
        QLineEdit *longValEdit = new QLineEdit(parent);
        MapValidator *longVal = new MapValidator( -180.0, 180.0, 8, longValEdit);
        longValEdit->setValidator( longVal );
        return longValEdit;
    }
    if (index.column() == 2)
    {
        QComboBox *comboBox = new QComboBox(parent);
        comboBox->addItem(QString("E"));
        comboBox->addItem(QString("W"));
        return comboBox;
    }

    //this checks the validation for the Latitude input
    if(index.column() == 3)
    {
        QLineEdit *latValEdit = new QLineEdit(parent);
        MapValidator *latVal = new MapValidator( -90.0, 90.0, 8, latValEdit);
        latValEdit->setValidator( latVal );
        return latValEdit;
    }

    else if (index.column() == 4){
        QComboBox *comboBox = new QComboBox(parent);
        comboBox->addItem(QString("N"));
        comboBox->addItem(QString("S"));
        return comboBox;
    }

    else if (index.column() == 5){
        QLineEdit *altValEdit = new QLineEdit(parent);
        MapValidator *altVal = new MapValidator( 0.0, 30000.0, 8, altValEdit);
        altValEdit->setValidator( altVal );
        return altValEdit;
    }

    else if (index.column() == 6){
        QLineEdit *velValEdit = new QLineEdit(parent);
        MapValidator *velVal = new MapValidator( 0.0, 30000000.0, 8, velValEdit);
        velValEdit->setValidator( velVal );
        return velValEdit;
    }
    else if (index.column() == 7) {
        QComboBox *comboBox = new QComboBox(parent);
        comboBox->addItem(QString("Behavior 1"));
        comboBox->addItem(QString("Behavior 2"));
        comboBox->addItem(QString("Behavior 3"));
        return comboBox;
    }
    return QItemDelegate::createEditor(parent, option, index);
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
