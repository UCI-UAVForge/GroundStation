#ifndef TIMER_WIDGET_H
#define TIMER_WIDGET_H

#include <QPlainTextEdit>
#include <QTimer>
#include "QTime"

class TimerWidget : public QPlainTextEdit
{
    Q_OBJECT
private:
    /// \brief Starting time
    QTime time;
    /// \brief Every time TimeTimer times out, the time on the GUI is updated by seeing how much time has passed since the starting time. Wow, I said 'time' a lot...
    QTimer TimeTimer;
    /// \brief The starting time as a string.
    QString start ;
public:
    /// \brief Default constructor.
    explicit TimerWidget(QWidget * parent = 0) ;
    /// \brief The imperative default destructor...
    ~TimerWidget();
    /// \brief Start the timer, and take note of the starting time.
    void initiate();
    /// \brief Stop the timer.
    void stop();
    /// \brief Get the starting time
    QTime getTime() const;
    /// \brief Set a new starting time
    void setTime(const QTime &value);
private slots:
    /// \brief Update the time in the GUI.
    void showTime() ;
};
#endif
