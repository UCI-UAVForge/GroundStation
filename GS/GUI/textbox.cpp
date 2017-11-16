#include "textbox.h"
#include <QPalette>

TextBox::TextBox(QWidget *parent) : QWidget(parent)
{
//    title = new QLabel();
//    text = new QLabel("N/A");
//    title->setAlignment(Qt::AlignHCenter);
//    title->setStyleSheet("QLabel {font-size:8pt; color: black}");
//    title->setContentsMargins(3, 8, 3, 0);
//    text->setAlignment(Qt::AlignHCenter);
//    text->setStyleSheet("QLabel {font-size: 12pt; color: " + textColor +";}");
//    text->setContentsMargins(3, 0, 3, 8);
//    QVBoxLayout* vbox = new QVBoxLayout();
//    vbox->addWidget(title);
//    vbox->addWidget(text);
//    vbox->setSpacing(0);
//    vbox->setContentsMargins(0,0,0,0);
//    setLayout(vbox);
//   // setPalette(QPalette::color("white"));
//    setStyleSheet("QLabel {background-color: white;}");
}

void TextBox::setTxt(const QString &t) {
   // text->setText(t);
}


void TextBox::setBgColor(const QString &color) {
   // setStyleSheet("QWidget {background-color:red;}");
}
