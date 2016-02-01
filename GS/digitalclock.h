#ifndef DIGITALCLOCK_H
#define DIGITALCLOCK_H


#include <QPlainTextEdit>
#include <QTime>
#include <QTimer>

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

    void initiate(QTime timein);

private slots:
    void showTime();
};

#endif // DIGITALCLOCK_H
