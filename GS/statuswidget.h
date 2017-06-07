#ifndef STATUS_WIDGET_H
#define STATUS_WIDGET_H

#include <QPlainTextEdit>
#include <QTimer>
#include "telemetrypacket.h"
#include "dataobjects.h"

//Definitions
#define EMPTY_TELEMETRY_PACKET NULL

class StatusWidget : public QPlainTextEdit
{
    Q_OBJECT
private:
    /// \brief Whenever StatusTimer times out, StatusWidget updates its GUI with info from currentTelemetryPacket.
	QTimer StatusTimer;
    /// \brief Pointer to some TelemetryPacket that reflects current UAV telemetry info
    Protocol::TelemetryPacket * currentTelemetryPacket ;

    TelemetryData currentTelemetryData;

public:
    /// \brief Default constructor. Takes no arguments.
    explicit StatusWidget(QWidget* parent=0);
    /// \brief Default destructor. Who even uses this?
	~StatusWidget();
    /// \brief Start the timer and clear the GUI
    void initiate();
    /// \brief Stop the timer.
    void stop() ;
    /// \brief Return the content of the TelemetryPacket.
    Protocol::TelemetryPacket getCurrentTelemetryPacket() ;
    /// \brief Tell StatusWidget to point to a different TelemetryPacket.
    void setCurrentTelemetryPacket( Protocol::TelemetryPacket * ) ;

    void setCurrentTelemetryData(TelemetryData *data);
public slots:
    /// \brief Slot called whenever StatusWidget updates its GUI. Update the GUI when StatusTimer times out.
    void showStatus();
};
#endif
