#ifndef DIGITALCLOCK_H
#define DIGITALCLOCK_H


#include <QPlainTextEdit>
#include <QTime>
#include <QTimer>

#include "messagebox.h"
class MapExecution;

/**
 * @brief The DigitalClock class
 * inherits from QPlainTextEdit
 * -Aaron Ko
 */
class DigitalClock : public QPlainTextEdit
{
    Q_OBJECT

public:
    DigitalClock(QWidget *parent = 0);

    QTime time;
    QString start;
    messagebox* mb;
    MapExecution* map_exec_ptr;

    void initiate(QTime timein);
    // Added mapexection pointer so that digital clock can connect to mapexecution.
    // Allows for connection to slots in mapexecution
    void initiate(messagebox* mbin, MapExecution* mapexec_ptr);

private slots:
    void showTime();
    void showStatus();
};

#endif // DIGITALCLOCK_H
