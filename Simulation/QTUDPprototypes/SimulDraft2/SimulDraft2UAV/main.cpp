#include "uav.h"
#include <QCoreApplication>
#include <QTextStream>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    QTextStream(stdout) << "run this shit";

    UAV uav;
//    uav.show();
//    return 0;
    return a.exec();
}
