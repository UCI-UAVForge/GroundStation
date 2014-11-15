/********************************************************************************
** Form generated from reading UI file 'options.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPTIONS_H
#define UI_OPTIONS_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Options
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;

    void setupUi(QWidget *Options)
    {
        if (Options->objectName().isEmpty())
            Options->setObjectName(QStringLiteral("Options"));
        Options->resize(688, 458);
        pushButton = new QPushButton(Options);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(230, 50, 181, 81));
        pushButton_2 = new QPushButton(Options);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(230, 160, 181, 81));
        pushButton_3 = new QPushButton(Options);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(230, 270, 181, 81));

        retranslateUi(Options);
        QObject::connect(pushButton, SIGNAL(clicked()), Options, SLOT(missionPlanningClicked()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), Options, SLOT(missionExecutionClicked()));
        QObject::connect(pushButton_3, SIGNAL(clicked()), Options, SLOT(missionRecapClicked()));

        QMetaObject::connectSlotsByName(Options);
    } // setupUi

    void retranslateUi(QWidget *Options)
    {
        Options->setWindowTitle(QApplication::translate("Options", "Form", 0));
        pushButton->setText(QApplication::translate("Options", "Mission Planning", 0));
        pushButton_2->setText(QApplication::translate("Options", "Mission Execution", 0));
        pushButton_3->setText(QApplication::translate("Options", "Mission Recap", 0));
    } // retranslateUi

};

namespace Ui {
    class Options: public Ui_Options {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPTIONS_H
