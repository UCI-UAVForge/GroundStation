#include "gscontrolpanel.h"
#include "ui_gscontrolpanel.h"

GSControlPanel::GSControlPanel(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::GSControlPanel)
{
    ui->setupUi(this);
}

GSControlPanel::~GSControlPanel()
{
    delete ui;
}
