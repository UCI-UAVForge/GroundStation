#ifndef QCOMBOBOXDELEGATE_H
#define QCOMBOBOXDELEGATE_H

#include <QItemDelegate>
#include <QComboBox>
#include <QModelIndex>
#include <QObject>
#include <QSize>
#include <QDoubleValidator>
#include <QLineEdit>

class QComboBoxDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit QComboBoxDelegate(QObject *parent = 0);
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
    void updateEditorGeometry(QWidget *editor,
                              const QStyleOptionViewItem &option,
                              const QModelIndex &index) const;

signals:

public slots:

};

#endif // QCOMBOBOXDELEGATE_H
