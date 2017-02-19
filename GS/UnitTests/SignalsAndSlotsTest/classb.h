#ifndef CLASSB_H
#define CLASSB_H

#include <QObject>

class ClassB : public QObject
{
    Q_OBJECT
public:
    explicit ClassB(QObject *parent = 0);
    ~ClassB();

signals:

public slots:
    void slotB() ;
};

#endif // CLASSB_H
