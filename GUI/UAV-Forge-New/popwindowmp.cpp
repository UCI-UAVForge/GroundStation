#include "popwindowmp.h"
#include "ui_popwindowmp.h"

PopWindowMP::PopWindowMP(QList<QList<QString> > list, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PopWindowMP)
{
    ui->setupUi(this);
    this->list = list;
}

PopWindowMP::~PopWindowMP()
{
    delete ui;
}

void PopWindowMP::on_pushButton_1_clicked()
{
    this->close();
}

void PopWindowMP::on_pushButton_2_clicked()
{
    this->close();
}
