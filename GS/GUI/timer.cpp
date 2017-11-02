#include "timer.h"
#include <QDebug>

Timer::Timer(QWidget *parent)
    : QLCDNumber(parent)
{
    setSegmentStyle(Filled);
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    timer->start(1000);
    time.setHMS(0,0,0);
    time.start();
    showTime();
}

void Timer::showTime()
{
    QTime *local = new QTime(0,0,0);
    *local = local->addMSecs(time.elapsed());
    QString text = local->toString("mm:ss");
    display(text);
}
