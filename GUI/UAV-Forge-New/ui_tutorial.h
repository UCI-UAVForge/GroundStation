/********************************************************************************
** Form generated from reading UI file 'tutorial.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
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

    void setupUi(QWidget *Tutorial)
    {
        if (Tutorial->objectName().isEmpty())
            Tutorial->setObjectName(QStringLiteral("Tutorial"));
        Tutorial->resize(720, 482);
        pushButton = new QPushButton(Tutorial);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(60, 70, 561, 331));

        retranslateUi(Tutorial);

        QMetaObject::connectSlotsByName(Tutorial);
    } // setupUi

    void retranslateUi(QWidget *Tutorial)
    {
        Tutorial->setWindowTitle(QApplication::translate("Tutorial", "Form", 0));
        pushButton->setText(QApplication::translate("Tutorial", "Tutorial Here", 0));
    } // retranslateUi

};

namespace Ui {
    class Tutorial: public Ui_Tutorial {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TUTORIAL_H
