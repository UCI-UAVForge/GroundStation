#include "maindockwindow.h"
#include "ui_maindockwindow.h"

MainDockWindow::MainDockWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainDockWindow)
{
    ui->setupUi(this);
}

MainDockWindow::~MainDockWindow()
{
    delete ui;
}
