#ifndef DIGITALCLOCK_H
#define DIGITALCLOCK_H


#include <QPlainTextEdit>
#include <QTime>
#include <QTimer>

#include "messagebox.h"

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
    messagebox mb;

    void initiate(QTime timein);
    void initiate(messagebox mbin);

private slots:
    void showTime();
    void showStatus();
};

#endif // DIGITALCLOCK_H
