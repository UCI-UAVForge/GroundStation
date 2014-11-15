/********************************************************************************
** Form generated from reading UI file 'mapexecution.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAPEXECUTION_H
#define UI_MAPEXECUTION_H

#include <QtCore/QVariant>
#include <QtWebKitWidgets/QWebView>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_mapexecution
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QWebView *webView;

    void setupUi(QWidget *mapexecution)
    {
        if (mapexecution->objectName().isEmpty())
            mapexecution->setObjectName(QStringLiteral("mapexecution"));
        mapexecution->resize(697, 471);
        pushButton = new QPushButton(mapexecution);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(160, 90, 291, 241));
        pushButton_2 = new QPushButton(mapexecution);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(530, 210, 121, 51));
        pushButton_3 = new QPushButton(mapexecution);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(530, 270, 121, 51));
        pushButton_4 = new QPushButton(mapexecution);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(530, 330, 121, 51));
        webView = new QWebView(mapexecution);
        webView->setObjectName(QStringLiteral("webView"));
        webView->setGeometry(QRect(59, 39, 461, 361));
        webView->setUrl(QUrl(QStringLiteral("about:blank")));

        retranslateUi(mapexecution);
        QObject::connect(pushButton_2, SIGNAL(clicked()), mapexecution, SLOT(finishClicked()));
        QObject::connect(pushButton_3, SIGNAL(clicked()), mapexecution, SLOT(returnHomeClicked()));
        QObject::connect(pushButton_4, SIGNAL(clicked()), mapexecution, SLOT(cancelClicked()));

        QMetaObject::connectSlotsByName(mapexecution);
    } // setupUi

    void retranslateUi(QWidget *mapexecution)
    {
        mapexecution->setWindowTitle(QApplication::translate("mapexecution", "Form", 0));
        pushButton->setText(QApplication::translate("mapexecution", "Map Display", 0));
        pushButton_2->setText(QApplication::translate("mapexecution", "Finish", 0));
        pushButton_3->setText(QApplication::translate("mapexecution", "Return home", 0));
        pushButton_4->setText(QApplication::translate("mapexecution", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class mapexecution: public Ui_mapexecution {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAPEXECUTION_H
