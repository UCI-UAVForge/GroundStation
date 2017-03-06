#ifndef TIMER_WIDGET_H
#define TIMER_WIDGET_H

#include <QPlainTextEdit>
#include <QTimer>
#include "QTime"

class TimerWidget : public QPlainTextEdit
{
    Q_OBJECT
private:

    QTime time;

    QTimer TimeTimer;

    QString start ;

public:
    TimerWidget(QWidget * parent = 0) ;
    //explicit TimerWidget(QWidget* parent = 0);

    ~TimerWidget();

    void initiate(QTime timein);

    QTime getTime() const;

    void setTime(const QTime &value);

    //QTimer getTimeTimer() const;

    //void setTimeTimer(QTimer newTimeTimer);

private slots:
    void showTime();

};
#endif
