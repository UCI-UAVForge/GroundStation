#include <QApplication>
#include "gscontrolpanel.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    GSControlPanel GSCP_TestObject ;

    GSCP_TestObject.show();

    return a.exec();
}
