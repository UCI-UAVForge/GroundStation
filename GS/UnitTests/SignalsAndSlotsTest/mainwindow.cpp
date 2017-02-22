#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    InstanceA = new ClassA() ;
    connect( InstanceA , SIGNAL( signalA() ) , &InstanceB , SLOT( slotB() ) ) ;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    delete InstanceA ;

}
