#include "qttabtest.h"
#include "ui_qttabtest.h"

QtTabTest::QtTabTest(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::QtTabTest)
{
    ui->setupUi(this);
}

QtTabTest::~QtTabTest()
{
    delete ui;
}
