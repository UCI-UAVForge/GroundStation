/********************************************************************************
** Form generated from reading UI file 'mapexecution.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
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
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QWebView *webView;
    QPushButton *pushButton;

    void setupUi(QWidget *mapexecution)
    {
        if (mapexecution->objectName().isEmpty())
            mapexecution->setObjectName(QStringLiteral("mapexecution"));
        mapexecution->resize(1366, 768);
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
        mapexecution->setPalette(palette);
        pushButton_2 = new QPushButton(mapexecution);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(720, 320, 121, 61));
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
        pushButton_3 = new QPushButton(mapexecution);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(720, 210, 121, 61));
        pushButton_3->setStyleSheet(QLatin1String(" QPushButton { \n"
"background-color: \"#CCD1D9\"; \n"
"color: \"#434A54\"; \n"
"border-radius: 10px;\n"
"font-weight: bold;\n"
"border: none; \n"
"}\n"
" QPushButton:pressed {\n"
"     background-color: #E6E9ED\n"
" }"));
        pushButton_4 = new QPushButton(mapexecution);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(720, 430, 121, 61));
        pushButton_4->setStyleSheet(QLatin1String(" QPushButton { \n"
"background-color: \"#CCD1D9\"; \n"
"color: \"#434A54\"; \n"
"border-radius: 10px;\n"
"font-weight: bold;\n"
"border: none; \n"
"}\n"
" QPushButton:pressed {\n"
"     background-color: #E6E9ED\n"
" }"));
        webView = new QWebView(mapexecution);
        webView->setObjectName(QStringLiteral("webView"));
        webView->setGeometry(QRect(190, 70, 491, 651));
        webView->setUrl(QUrl(QStringLiteral("about:blank")));
        pushButton = new QPushButton(mapexecution);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(720, 550, 121, 61));
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

        retranslateUi(mapexecution);
        QObject::connect(pushButton_2, SIGNAL(clicked()), mapexecution, SLOT(finishClicked()));
        QObject::connect(pushButton_3, SIGNAL(clicked()), mapexecution, SLOT(returnHomeClicked()));
        QObject::connect(pushButton_4, SIGNAL(clicked()), mapexecution, SLOT(cancelClicked()));

        QMetaObject::connectSlotsByName(mapexecution);
    } // setupUi

    void retranslateUi(QWidget *mapexecution)
    {
        mapexecution->setWindowTitle(QApplication::translate("mapexecution", "Form", 0));
        pushButton_2->setText(QApplication::translate("mapexecution", "Finish", 0));
        pushButton_3->setText(QApplication::translate("mapexecution", "Return home", 0));
        pushButton_4->setText(QApplication::translate("mapexecution", "Cancel", 0));
        pushButton->setText(QApplication::translate("mapexecution", "Back", 0));
    } // retranslateUi

};

namespace Ui {
    class mapexecution: public Ui_mapexecution {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAPEXECUTION_H
