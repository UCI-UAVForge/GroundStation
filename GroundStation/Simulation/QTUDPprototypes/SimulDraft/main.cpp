#include <QCoreApplication>
#include <QString>
#include <QTextStream>
#include <QDebug>
#include <QUdpSocket>

#include <groundstation.h>

#include <string>
#include <iostream>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QString strng = "hello";
    QTextStream(stdout) << strng << endl;

    GroundStation testServer;
    testServer.initSocket();



    QCoreApplication::exit(0);
    return 0;
//    return a.exec();
}

