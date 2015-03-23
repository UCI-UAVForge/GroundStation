/********************************************************************************
** Form generated from reading UI file 'mapexecution.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
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
    QPushButton *pushBtnStop;
    QPushButton *pushBtnReturnHome;
    QPushButton *pushBtnCancel;
    QWebView *webView;
    QPushButton *pushButton;
    QPushButton *pushBtnFinish;

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
        pushBtnStop = new QPushButton(mapexecution);
        pushBtnStop->setObjectName(QStringLiteral("pushBtnStop"));
        pushBtnStop->setGeometry(QRect(940, 400, 121, 51));
        pushBtnStop->setStyleSheet(QLatin1String(" QPushButton { \n"
"background-color: \"#CCD1D9\"; \n"
"color: \"#434A54\"; \n"
"border-radius: 10px;\n"
"font-weight: bold;\n"
"border: none; \n"
"}\n"
" QPushButton:pressed {\n"
"     background-color: #E6E9ED\n"
" }"));
        pushBtnReturnHome = new QPushButton(mapexecution);
        pushBtnReturnHome->setObjectName(QStringLiteral("pushBtnReturnHome"));
        pushBtnReturnHome->setGeometry(QRect(940, 470, 121, 51));
        pushBtnReturnHome->setStyleSheet(QLatin1String(" QPushButton { \n"
"background-color: \"#CCD1D9\"; \n"
"color: \"#434A54\"; \n"
"border-radius: 10px;\n"
"font-weight: bold;\n"
"border: none; \n"
"}\n"
" QPushButton:pressed {\n"
"     background-color: #E6E9ED\n"
" }"));
        pushBtnCancel = new QPushButton(mapexecution);
        pushBtnCancel->setObjectName(QStringLiteral("pushBtnCancel"));
        pushBtnCancel->setGeometry(QRect(940, 540, 121, 51));
        pushBtnCancel->setStyleSheet(QLatin1String(" QPushButton { \n"
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
        webView->setGeometry(QRect(80, 70, 800, 650));
        webView->setUrl(QUrl(QStringLiteral("about:blank")));
        pushButton = new QPushButton(mapexecution);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(80, 30, 75, 23));
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
        pushBtnFinish = new QPushButton(mapexecution);
        pushBtnFinish->setObjectName(QStringLiteral("pushBtnFinish"));
        pushBtnFinish->setGeometry(QRect(940, 330, 121, 51));
        pushBtnFinish->setStyleSheet(QLatin1String(" QPushButton { \n"
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
        QObject::connect(pushBtnFinish, SIGNAL(clicked()), mapexecution, SLOT(finishClicked()));
        QObject::connect(pushBtnReturnHome, SIGNAL(clicked()), mapexecution, SLOT(returnHomeClicked()));
        QObject::connect(pushBtnCancel, SIGNAL(clicked()), mapexecution, SLOT(cancelClicked()));

        QMetaObject::connectSlotsByName(mapexecution);
    } // setupUi

    void retranslateUi(QWidget *mapexecution)
    {
        mapexecution->setWindowTitle(QApplication::translate("mapexecution", "Form", 0));
        pushBtnStop->setText(QApplication::translate("mapexecution", "Stop", 0));
        pushBtnReturnHome->setText(QApplication::translate("mapexecution", "Return home", 0));
        pushBtnCancel->setText(QApplication::translate("mapexecution", "Cancel", 0));
        pushButton->setText(QApplication::translate("mapexecution", "Back", 0));
        pushBtnFinish->setText(QApplication::translate("mapexecution", "Finish", 0));
    } // retranslateUi

};

namespace Ui {
    class mapexecution: public Ui_mapexecution {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAPEXECUTION_H
