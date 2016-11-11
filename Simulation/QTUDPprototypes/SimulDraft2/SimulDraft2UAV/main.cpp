#include "uav.h"
#include <QCoreApplication>
#include <QTextStream>
int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    UAV uav;
    return a.exec();
}
