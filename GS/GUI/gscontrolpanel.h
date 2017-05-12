#ifndef GSCONTROLPANEL_H
#define GSCONTROLPANEL_H

#include <QDialog>
#include "telemetrypacket.h"
#include "dataobjects.h"
#define EMPTY_TELEMETRY_PACKET NULL

namespace Ui {
    class GSControlPanel;
}

enum GSCPState {
    MainMenuState , LoadFlightpathState , PlanningState , LoadMissionState , ExecutionState , RecapState
};

class GSControlPanel : public QDialog {

    Q_OBJECT

public:
    explicit GSControlPanel(QWidget *parent = 0);
    ~GSControlPanel();
  
    QString getMissionNameToSave() ;
    QString getMissionNameToLoad() ;
    void addMissionToLoad( QString ) ;
    QString getFlightpathNameToSave() ;
    QString getFlightpathNameToLoad() ;
    void addFlightpathToLoad( QString ) ;
    //void setCurrentTelemetryPacket( Protocol::TelemetryPacket * ) ;

    void setCurrentTelemetryData(TelemetryData *data);

    void setSelectedMission(QString text);

private:
    Ui::GSControlPanel *ui;
    GSCPState CurrentState;
    static GSCPState persistantState;

    QString folder;
    const char kPathSeparator =
        #ifdef _WIN32
                                '\\';
        #else
                                '/';
        #endif

private slots:
    void on_StartMissionButton_clicked();
    void on_FinishMissionButton_clicked();
    void on_LoadMissionButton_clicked();
    void on_SaveMissionButton_clicked();
    void on_ClearPointsButton_clicked();
    void on_ExitButton_clicked();
    void on_CreateMissionButton_clicked();
    void on_LoadFlightpathButton_clicked();
    void on_MainMenuButton_clicked();
    void on_SaveFlightpathButton_clicked();
    void on_MissionRecapButton_clicked();
    void updateStateGSCP( ) ;

signals:
    ///\todo Are these signals redundant? Qt may already provide them. Oh, well...
    void startMissionButton_clicked();
    void finishMissionButton_clicked();
    void loadMissionButton_clicked();
    void saveMissionButton_clicked();
    void clearPointsButton_clicked();
    void exitButton_clicked();
    void createMissionButton_clicked();
    void loadFlightpathButton_clicked();
    void mainMenuButton_clicked() ;
    void saveFlightpathButton_clicked() ;
    void missionRecapButton_clicked() ;
    /// @brief Used to inform GSControlPanel to update its GUI when it changes state
    void updateGSCP() ;

    ///These signals are emitted once you enter their corresponding state.
    void inMainMenuState() ;
    void inLoadFlightpathState() ;
    void inPlanningState() ;
    void inLoadMissionState() ;
    void inExecutionState() ;
    void inRecapState() ;
    void inUndefinedState() ;
};

#endif // GSCONTROLPANEL_H
