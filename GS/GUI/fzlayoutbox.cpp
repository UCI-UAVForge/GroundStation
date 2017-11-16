#include "fzlayoutbox.h"

fzLayoutBox::fzLayoutBox(): QGridLayout()
{
//    title = new QLabel(t);
//    title->setAlignment(Qt::AlignCenter);
//    title->setStyleSheet("QLabel {background-color: white;}");
//    this->addWidget(title,0,0,1,2);
    QLabel * temp = new QLabel("altitude_msl_min");
    temp->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    temp->setStyleSheet("QLabel {background-color: white;}");
    this->addWidget(temp,0,0,1,3);

    nmin  = new QLabel("N/A");
    nmin->setAlignment(Qt::AlignCenter);
    nmin->setStyleSheet("QLabel {background-color: white; color: red;}");
    this->addWidget(nmin,0,3,1,1);

    temp = new QLabel("altitude_msl_max");
    temp->setAlignment(Qt::AlignLeft | Qt::AlignVCenter);
    temp->setStyleSheet("QLabel {background-color: white;}");
    this->addWidget(temp,0,4,1,3);

    nmax  = new QLabel("N/A");
    nmax->setAlignment(Qt::AlignCenter);
    nmax->setStyleSheet("QLabel {background-color: white; color: blue;}");
    this->addWidget(nmax,0,7,1,1);
}

void fzLayoutBox::setMinMax(QString mini, QString maxi){
    nmin->setText(mini);
    nmax->setText(maxi);
}
