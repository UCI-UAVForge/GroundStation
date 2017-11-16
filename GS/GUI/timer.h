#ifndef TIMER_H
#define TIMER_H

#include <QLCDNumber>
#include <QTime>
#include <QTimer>

class Timer : public QLCDNumber
{
    Q_OBJECT
public:
    Timer(QWidget * parent = 0);
    QTime time;
    QTimer *timer;
private slots:
    void showTime();
signals:
    void timeChanged();
};
#endif // TIMER_H
