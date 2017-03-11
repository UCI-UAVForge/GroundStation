#include "classb.h"
#include <QDebug>
#include <QTime>

ClassB::ClassB(QObject *parent) : QObject(parent)
{

}

ClassB::~ClassB()
{

}

void ClassB::slotB() {

    qDebug() << "Signal A was just emitted and slot B is currently being called." ;
    qDebug() << "We're gonna wait 5 seconds before the function that called this slot can continue.";
    QTime finish = QTime::currentTime().addSecs(5) ;
    while ( QTime::currentTime() < finish ) ;
    qDebug() << "Okay that's enough for now. Slot B is finished." ;

}
