#include "toolbar.h"
#include "ui_toolbar.h"

ToolBar::ToolBar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ToolBar)
{
    ui->setupUi(this);
}

ToolBar::~ToolBar()
{
    delete ui;
}
