#include "classa.h"
#include <QDebug>

ClassA::ClassA(QObject *parent) : QObject(parent)
{

}

ClassA::~ClassA()
{

    emit signalA() ;
    qDebug() << "Control is returned back to the function that emitted the signal." ;

}
