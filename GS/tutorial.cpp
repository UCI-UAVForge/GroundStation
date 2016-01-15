#include "tutorial.h"
#include "ui_tutorial.h"
#include "mainwindow.h"

Tutorial::Tutorial(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tutorial)
{
    ui->setupUi(this);
    QPixmap picture("res/images/UAVTutorialTest.png");
    ui->label_picture->setPixmap(picture);
    connect(ui->backButton, SIGNAL(clicked()), this, SLOT(on_backButton_clicked()), Qt::UniqueConnection);

}

Tutorial::~Tutorial()
{
    delete ui;
}

void Tutorial::on_backButton_clicked()
{

    this -> close();

}
