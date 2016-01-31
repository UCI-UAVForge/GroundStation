#include "connectiondialog.h"
#include "ui_connectiondialog.h"

ConnectionDialog::ConnectionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ConnectionDialog)
{
    ui->setupUi(this);

}

void ConnectionDialog::closeConnectionDialog()
{
    this->close();
}

void ConnectionDialog::on_OK_button_clicked() {
    this->close();
}


ConnectionDialog::~ConnectionDialog()
{
    delete ui;
}

