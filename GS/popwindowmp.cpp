#include "popwindowmp.h"
#include "ui_popwindowmp.h"
#include <QString>
#include <QDebug>
#include "mapexecution.h"

PopWindowMP::PopWindowMP(QList<QString> strings, QWidget *parent) : QWidget(parent), ui(new Ui::PopWindowMP) {
    ui->setupUi(this);
    mapStrings = strings;
//    connect(ui->yesButton,SIGNAL(clicked()),this,SLOT(yesButtonClicked()));
}

PopWindowMP::~PopWindowMP() {
    delete ui;
}

void PopWindowMP::on_yesButton_clicked() {
    MapExecution *mapExecution = new MapExecution(mapStrings);
    mapExecution->show();
    emit(windowClosed());
    this -> close();
}

void PopWindowMP::on_noButton_clicked() {
    this->close();
}
