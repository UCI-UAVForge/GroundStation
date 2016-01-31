#include "digitalclock.h"

#include <QtWidgets>

#include "digitalclock.h"

DigitalClock::DigitalClock(QWidget *parent)
    : QPlainTextEdit(parent)
{
    //setSegmentStyle(Filled);



    //setWindowTitle(tr("Digital Clock"));
    //resize(150, 60);
}

/**
 * @brief DigitalClock::initiate
 * saves start time (need to fix to get from message box)
 * connects 1 second timer to showtime function
 */
void DigitalClock::initiate(QTime timein)
{
    start = QTime::currentTime().toString("hh:mm:ss");
    time = timein;
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    timer->start(1000);

    showTime();
}

void DigitalClock::initiate(messagebox mbin)
{
    mb = mbin;
    QTimer *timer2 = new QTimer(this);
    connect(timer2, SIGNAL(timeout()), this, SLOT(showStatus()));
    timer2->start(200);

    showStatus();
}

/**
 * @brief DigitalClock::showTime
 * creates string from elapsed time and starting time
 * clears the PlainText and updates it
 */
void DigitalClock::showTime()
{
    QString text;
    text = "Started: ";
    text.append(start);
    text.append("\nElapsed: ");
    int elapsed = time.elapsed();
    elapsed = elapsed;
    QTime time2(00, 00, 00);
    time2 = time2.addMSecs(elapsed);
    text.append(time2.toString("hh:mm:ss"));
    clear();
    appendPlainText(text);
}

void DigitalClock::showStatus()
{
    float vX;
    float vY;
    float vZ;
    float pitch;
    float roll;
    float yaw;
    double lat;
    double lon;
    float alt;
    float heading;
    if (mb.get_telem_packets().empty())
    {
        clear();
        appendPlainText("Empty: ");
        appendPlainText(QTime::currentTime().toString("hh:mm:ss"));
    }
    else
    {
        Protocol::TelemetryPacket last = mb.get_telem_packets().back();
        last.GetVelocity(&vX, &vY,&vZ);
        QString text;
        text.append("Velocity: ");
        text.append(QString::number(vX,'f',2) + ', ' + QString::number(vY,'f',2) + ', ' + QString::number(vZ,'f',2));
        clear();
        appendPlainText(text);
    }
}
