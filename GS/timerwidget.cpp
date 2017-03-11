#include "timerwidget.h"

/// \todo Doxygen comments. Standardize getter and setter methods in TimerWidget and StatusWidget classes.

TimerWidget::TimerWidget( QWidget* parent ) : QPlainTextEdit( parent ) , time() , TimeTimer() {

    connect(&TimeTimer, SIGNAL(timeout()), this, SLOT(showTime()));

}

//explicit TimerWidget::TimerWidget(QWidget* parent) : QPlainTextEdit(parent)
//{
//    connect(&TimeTimer, SIGNAL(timeout()), this, SLOT(showTime()));
//}

TimerWidget::~TimerWidget()
{
}

QTime TimerWidget::getTime() const
{
    return time;
}

void TimerWidget::setTime(const QTime &value)
{
    time = value;
}

//QTimer TimerWidget::getTimeTimer() const
//{
//    return TimeTimer ;
//}

//void TimerWidget::setTimeTimer(QTimer newTimeTimer)
//{
//    TimeTimer = newTimeTimer;
//}

void TimerWidget::showTime()
{
    QString text;
    text = "Started: ";
    text.append(start);
    text.append("\nElapsed: ");
    int elapsed = time.elapsed();
    QTime time2(00, 00, 00);
    time2 = time2.addMSecs(elapsed);
    text.append(time2.toString("hh:mm:ss"));
    clear();
    appendPlainText(text);
}

void TimerWidget::initiate(QTime timein)
{
    start = QTime::currentTime().toString("hh:mm:ss");
    time = timein;
    TimeTimer.start(1000);
    /// \todo Is this showTime necessary?
    showTime();
}
