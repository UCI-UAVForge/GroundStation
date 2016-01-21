#include <QCoreApplication>
#include <QTextStream>
#include <QString>


#include <groundstation.h>
#include "Packet.h"
#include "telemetrypacket.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    QTextStream(stdout) << "run this";



    GroundStation station;


//    return 0;
   return a.exec();
}


