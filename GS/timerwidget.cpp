#include "timerwidget.h"

TimerWidget::TimerWidget( QWidget* parent ) : QPlainTextEdit( parent ) , time() , TimeTimer() {
    connect(&TimeTimer, SIGNAL(timeout()), this, SLOT(showTime()));
}

TimerWidget::~TimerWidget() {}

QTime TimerWidget::getTime() const {
    return time;
}

void TimerWidget::setTime(const QTime &value) {
    time = value;
}

void TimerWidget::showTime() {
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

void TimerWidget::initiate() {
    TimeTimer.start(1000);
    time = QTime::currentTime();
    start = time.toString("hh:mm:ss");
    showTime();
}

void TimerWidget::stop() {
    TimeTimer.stop();
}
