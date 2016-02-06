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
