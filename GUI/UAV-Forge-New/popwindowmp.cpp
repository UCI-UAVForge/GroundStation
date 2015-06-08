#include "popwindowmp.h"
#include "ui_popwindowmp.h"
#include <QString>
#include <QDebug>
#include "mapexecution.h"

PopWindowMP::PopWindowMP(QList<QString> strings, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PopWindowMP)
{
    ui->setupUi(this);
    mapStrings = strings;
    connect(ui->pushButton,SIGNAL(clicked()),this,SLOT(yesButtonClicked()));
}

PopWindowMP::~PopWindowMP()
{
    delete ui;
}

void PopWindowMP::yesButtonClicked(){
    MapExecution *mapExecution = new MapExecution(mapStrings);
    mapExecution->show();
    emit(windowClosed());
    this -> close();
}

void PopWindowMP::on_pushButton_2_clicked()
{
    this->close();
}
