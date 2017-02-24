#ifndef MISSIONSTATUSWINDOW_H
#define MISSIONSTATUSWINDOW_H

#include <QDialog>

namespace Ui {
class MissionStatusWindow;
}

///\todo Hmmm... Is that right?
//Forward declare TelemetryPacket to avoid including useless headers.
namespace Protocol { class TelemetryPacket; }

class MissionStatusWindow : public QDialog
{
    Q_OBJECT

public:
    explicit MissionStatusWindow(QWidget *parent = 0);
    ~MissionStatusWindow();

    ///\todo Return boolean for successful or failed initiation

    void initiateWidgets() ;

    void initiateStatusWidget() ;

    void initiateTimerWidget() ;

    void setCurrentTelemetryPacket( Protocol::TelemetryPacket * ) ;

signals:
    void updateStatusWidget() ;

private:
    Ui::MissionStatusWindow *ui;

    Protocol::TelemetryPacket * currentTelemetryPacket ;
};

#endif // MISSIONSTATUSWINDOW_H
