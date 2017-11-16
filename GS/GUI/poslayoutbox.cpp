#include "poslayoutbox.h"

posLayoutBox::posLayoutBox(QString t, QString la, QString lo, QWidget *parent) : QGridLayout(parent)
{
    title = new QLabel(t);
    title->setAlignment(Qt::AlignCenter);
    title->setStyleSheet("QLabel {background-color: white;}");
    this->addWidget(title,0,0,1,2);

    lat  = new QLabel(la);
    lat->setAlignment(Qt::AlignCenter);
    lat->setStyleSheet("QLabel {background-color: white; color: red;}");
    this->addWidget(lat,1,0,1,1);

    lon  = new QLabel(lo);
    lon->setAlignment(Qt::AlignCenter);
    lon->setStyleSheet("QLabel {background-color: white; color: blue;}");
    this->addWidget(lon,1,1,1,1);
}

void posLayoutBox::setLatLon(QString la, QString lo){
    lat->setText(la);
    lon->setText(lo);
}
