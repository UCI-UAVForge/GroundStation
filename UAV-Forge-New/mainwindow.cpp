#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "options.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::openOptions()
{
    Options *options = new Options();
    options -> show();
}
