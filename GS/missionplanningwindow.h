#ifndef MISSIONPLANNINGWINDOW_H
#define MISSIONPLANNINGWINDOW_H

#include <QDialog>
#include "qpushbutton.h"
#include "QHBoxLayout"
#include "QVBoxLayout"
#include "QGridLayout"
#include "qcombobox.h"

//Code by David Moe

class MissionPlanningWindow : public QDialog
{
    Q_OBJECT

public:
    MissionPlanningWindow(QWidget *parent = 0);
    ~MissionPlanningWindow();

    /* TODO Roman Parise - temporary function. Please replace later */
    void deleteExecuteButton();

    void addButton( QPushButton * );

private:
    QPushButton *executeButton;
    QComboBox *uavComboBox;
    QComboBox *missionPlanComboBox;
    QGridLayout *layout;
    QHBoxLayout * buttonLayout;
    QVBoxLayout * superLayout;

private slots:
    //void setExecutionButtonEnabled();
};

#endif // MISSIONPLANNINGWINDOW_H
