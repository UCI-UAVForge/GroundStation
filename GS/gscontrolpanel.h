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
    QString getMissionNameToSave();
    QString getMissionNameToLoad();
    void addMissionToLoad( QString );
    void setSelectedMission(QString text);

private slots:
    void on_StartMissionButton_clicked();
    void on_FinishMissionButton_clicked();
    void on_LoadMissionButton_clicked();
    void on_SaveMissionButton_clicked();
    void on_ClearPointsButton_clicked();
    void on_ExitButton_clicked();
    void on_CreateMissionButton_clicked();

private:
    Ui::GSControlPanel *ui;

signals:
    void startMissionButton_clicked();
    void finishMissionButton_clicked();
    void loadMissionButton_clicked();
    void saveMissionButton_clicked();
    void clearPointsButton_clicked();
    void exitButton_clicked();
    void createMissionButton_clicked();
};

#endif // GSCONTROLPANEL_H
