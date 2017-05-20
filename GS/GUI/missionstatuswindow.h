#ifndef MISSIONSTATUSWINDOW_H
#define MISSIONSTATUSWINDOW_H

#include <QDialog>
#include "telemetrypacket.h"
#include "dataobjects.h"

namespace Ui {
    class MissionStatusWindow;
}

class MissionStatusWindow : public QDialog
{
    Q_OBJECT
public:
    /// \brief Default constructor.
    explicit MissionStatusWindow(QWidget *parent = 0);
    /// \brief Default destructor.
    ~MissionStatusWindow();
    /// \brief Inititate TimerWidget and StatusWidget.
    void initiateWidgets() ;
    /// \brief Initiate StatusWidget
    void initiateStatusWidget() ;
    /// \brief Initiate TimerWidget
    void initiateTimerWidget() ;
    /// \brief Set the current telemetry packet in MissionStatusWindow and StatusWidget.
    //void setCurrentTelemetryPacket( Protocol::TelemetryPacket * ) ;

    void setCurrentTelemetryData(TelemetryData *data);

    /// \brief Stop StatusWidget and TimerWidget
    void stopWidgets() ;
    /// \brief Stop StatusWidget
    void stopStatusWidget() ;
    /// \brief Stop TimerWidget
    void stopTimerWidget() ;
private:
    /// \brief UI object for the GUI. The GUI acts as a container for the StatusWidget and TimerWidget GUI objects.
    Ui::MissionStatusWindow *ui;
    /// \brief A pointer to the TelemetryPacket with the most recent information on the UAV.
    //Protocol::TelemetryPacket * currentTelemetryPacket ;

    TelemetryData *currentTelemetryData;
};

#endif // MISSIONSTATUSWINDOW_H
