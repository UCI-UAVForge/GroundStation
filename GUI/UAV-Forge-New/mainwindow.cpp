#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "options.h"
#include "tutorial.h"
#include <QtWebKitWidgets/QWebView>
#include <QUrl>

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

void MainWindow::openTutorial()
{
    Tutorial *tutorial = new Tutorial();
    tutorial -> show();
}
