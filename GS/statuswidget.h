#ifndef STATUS_WIDGET_H
#define STATUS_WIDGET_H

#include "QPlainTextEdit.h"
#include "QTimer.h"
#include "QString.h"
#include "QObject.h"
#include "messagebox.h"

///\todo Make this a definition for the entire project?
//Definitions
#define EMPTY_TELEMETRY_PACKET NULL

class StatusWidget : public QPlainTextEdit
{
    Q_OBJECT
private:
	QTimer StatusTimer;

	QString start;

public:
    explicit StatusWidget(QWidget* parent=0);

	~StatusWidget();

    void initiate();

    /*QTimer getStatusTimer();

    void setStatusTimer(QTimer newStatusTimer);*/

    void showStatus( Protocol::TelemetryPacket * );

signals:

    void updateMe() ;

};
#endif
