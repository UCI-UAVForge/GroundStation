#ifndef CLASSA_H
#define CLASSA_H

#include <QObject>

class ClassA : public QObject
{
    Q_OBJECT
public:
    explicit ClassA(QObject *parent = 0);
    ~ClassA();

signals:

    void signalA() ;

public slots:
};

#endif // CLASSA_H
