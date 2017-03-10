#ifndef MISSIONPLANNINGWINDOW_H
#define MISSIONPLANNINGWINDOW_H

#include <QDialog>
#include "qpushbutton.h"
#include "QHBoxLayout"
#include "QVBoxLayout"
#include "QGridLayout"
#include "qcombobox.h"
#include <QDebug>
#include <QLineEdit>
#include <QLabel>

//Code by David Moe

class MissionPlanningWindow : public QDialog
{
    Q_OBJECT

    friend class MainMDIDisplay;

public:
    MissionPlanningWindow(QWidget *parent = 0);
    ~MissionPlanningWindow();

    /* TODO Roman Parise - temporary function. Please replace later */
    void deleteExecuteButton();

    void addButton( QPushButton * );

    void addComboBox( QComboBox * );

    void addTextBox( QLineEdit * );

    void addTextBox( QLineEdit * , QLabel * );

    void dumpButtons();

    void dumpComboBoxes();

    void changeTitle( QString ) ;

    //Return value of uavComboBox
    QString getUAV() ;

    //Return value of missionPlanComboBox
    QString getMission() ;

private:
    QPushButton *executeButton;
    QComboBox *uavComboBox;
    QComboBox *missionPlanComboBox;
    QGridLayout *layout;
    QHBoxLayout * buttonLayout;
    QHBoxLayout * textBoxLayout;
    QVBoxLayout * superLayout;

    QList<QPushButton *> buttonList;

    QList<QComboBox *> comboBoxList;

    QList<QLineEdit *> textBoxList;

    QList<QLabel *> textBoxLabelList;

private slots:
    //void setExecutionButtonEnabled();
};

#endif // MISSIONPLANNINGWINDOW_H
