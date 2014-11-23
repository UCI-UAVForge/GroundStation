/********************************************************************************
** Form generated from reading UI file 'popwindowmp.ui'
**
** Created by: Qt User Interface Compiler version 5.3.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_POPWINDOWMP_H
#define UI_POPWINDOWMP_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PopWindowMP
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label;

    void setupUi(QWidget *PopWindowMP)
    {
        if (PopWindowMP->objectName().isEmpty())
            PopWindowMP->setObjectName(QStringLiteral("PopWindowMP"));
        PopWindowMP->resize(400, 300);
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush);
        QBrush brush1(QColor(67, 74, 84, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        PopWindowMP->setPalette(palette);
        pushButton = new QPushButton(PopWindowMP);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(60, 150, 121, 51));
        pushButton->setStyleSheet(QLatin1String(" QPushButton { \n"
"background-color: \"#ffffff\"; \n"
"color: \"#434A54\"; \n"
"border-radius: 10px;\n"
"font-weight: bold;\n"
"font-size: 20px;\n"
"border: none; \n"
"}\n"
" QPushButton:pressed {\n"
"     background-color: #E6E9ED\n"
" }"));
        pushButton_2 = new QPushButton(PopWindowMP);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(220, 150, 121, 51));
        pushButton_2->setStyleSheet(QLatin1String(" QPushButton { \n"
"background-color: \"#ffffff\"; \n"
"color: \"#434A54\"; \n"
"border-radius: 10px;\n"
"font-weight: bold;\n"
"font-size: 20px;\n"
"border: none; \n"
"}\n"
" QPushButton:pressed {\n"
"     background-color: #E6E9ED\n"
" }"));
        label = new QLabel(PopWindowMP);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(60, 40, 281, 41));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        label->setFont(font);
        label->setStyleSheet(QLatin1String("color: #ffffff;\n"
"font-weight: bold;\n"
""));

        retranslateUi(PopWindowMP);

        QMetaObject::connectSlotsByName(PopWindowMP);
    } // setupUi

    void retranslateUi(QWidget *PopWindowMP)
    {
        PopWindowMP->setWindowTitle(QApplication::translate("PopWindowMP", "Form", 0));
        pushButton->setText(QApplication::translate("PopWindowMP", "Yes", 0));
        pushButton_2->setText(QApplication::translate("PopWindowMP", "No", 0));
        label->setText(QApplication::translate("PopWindowMP", "Are you sure you want to execute?", 0));
    } // retranslateUi

};

namespace Ui {
    class PopWindowMP: public Ui_PopWindowMP {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_POPWINDOWMP_H
