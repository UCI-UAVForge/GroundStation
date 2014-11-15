/********************************************************************************
** Form generated from reading UI file 'popwindowmp.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
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
        pushButton = new QPushButton(PopWindowMP);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(60, 150, 121, 51));
        pushButton_2 = new QPushButton(PopWindowMP);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(190, 150, 121, 51));
        label = new QLabel(PopWindowMP);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(60, 40, 281, 41));
        QFont font;
        font.setPointSize(16);
        font.setBold(false);
        font.setWeight(50);
        label->setFont(font);

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
