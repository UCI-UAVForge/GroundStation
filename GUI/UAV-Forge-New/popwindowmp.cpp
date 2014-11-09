#include "popwindowmp.h"
#include "ui_popwindowmp.h"

PopWindowMP::PopWindowMP(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::PopWindowMP)
{
    ui->setupUi(this);
}

PopWindowMP::~PopWindowMP()
{
    delete ui;
}

void PopWindowMP::on_pushButton_2_clicked()
{
    this->close();
}
