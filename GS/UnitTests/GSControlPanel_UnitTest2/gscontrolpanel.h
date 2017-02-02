#ifndef GSCONTROLPANEL_H
#define GSCONTROLPANEL_H

#include <QDialog>

namespace Ui {

    class GSControlPanel;

}

class GSControlPanel : public QDialog {

    Q_OBJECT

public:

    explicit GSControlPanel(QWidget *parent = 0);

    ~GSControlPanel();

private slots:
    void on_StartMissionButton_clicked();

    void on_FinishMissionButton_clicked();

    void on_LoadMissionButton_clicked();

    void on_SaveMissionButton_clicked();

    void on_ClearPointsButton_clicked();

    void on_ExitButton_clicked();

private:

    Ui::GSControlPanel *ui;

};

#endif // GSCONTROLPANEL_H
