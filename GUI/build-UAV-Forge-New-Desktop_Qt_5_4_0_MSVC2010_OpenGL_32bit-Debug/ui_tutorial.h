/********************************************************************************
** Form generated from reading UI file 'tutorial.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TUTORIAL_H
#define UI_TUTORIAL_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Tutorial
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;

    void setupUi(QWidget *Tutorial)
    {
        if (Tutorial->objectName().isEmpty())
            Tutorial->setObjectName(QStringLiteral("Tutorial"));
        Tutorial->resize(720, 482);
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
        Tutorial->setPalette(palette);
        pushButton = new QPushButton(Tutorial);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(60, 70, 561, 331));
        pushButton->setStyleSheet(QLatin1String(" QPushButton { \n"
"background-color: \"#CCD1D9\"; \n"
"color: \"#434A54\"; \n"
"border-radius: 10px;\n"
"font-weight: bold;\n"
"border: none; \n"
"}\n"
" QPushButton:pressed {\n"
"     background-color: #E6E9ED\n"
" }"));
        pushButton_2 = new QPushButton(Tutorial);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(60, 30, 75, 23));
        pushButton_2->setStyleSheet(QLatin1String(" QPushButton { \n"
"background-color: \"#CCD1D9\"; \n"
"color: \"#434A54\"; \n"
"border-radius: 10px;\n"
"font-weight: bold;\n"
"border: none; \n"
"}\n"
" QPushButton:pressed {\n"
"     background-color: #E6E9ED\n"
" }"));

        retranslateUi(Tutorial);

        QMetaObject::connectSlotsByName(Tutorial);
    } // setupUi

    void retranslateUi(QWidget *Tutorial)
    {
        Tutorial->setWindowTitle(QApplication::translate("Tutorial", "Form", 0));
        pushButton->setText(QApplication::translate("Tutorial", "Tutorial Here", 0));
        pushButton_2->setText(QApplication::translate("Tutorial", "Back", 0));
    } // retranslateUi

};

namespace Ui {
    class Tutorial: public Ui_Tutorial {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TUTORIAL_H
