#ifndef MISSIONTABLE_H
#define MISSIONTABLE_H

#include <QTableView>
#include <QKeyEvent>
#include <QHeaderView>
#include <QStandardItemModel>

class MissionTable : public QTableView
{
    Q_OBJECT
public:
    MissionTable();
    explicit MissionTable(QWidget *parent = nullptr);
    void keyPressEvent(QKeyEvent * key);
    void focusInEvent(QFocusEvent * e);
    void focusOutEvent(QFocusEvent * e);
    int current;
    void selectChanged(const QItemSelection & selected, const QItemSelection & deselected);
    void modelChanged(QAbstractItemModel *model);
    void setTableModel(QStandardItemModel * model);

    //void changeParams(QStandardItem * item);

signals:
    void moveWaypoint(int wpNum, int key);
    void addWaypoint(int wpNum);
    void removeWaypoint(int wpNum);
    void selectWaypoint(int wpNum);
    void editMode(bool editing);
    void changeParams(QStandardItem *item);

private:
    bool isInterop;
};

#endif // MISSIONTABLE_H
