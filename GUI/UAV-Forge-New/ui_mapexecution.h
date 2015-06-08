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

class Ui_MapExecution
{
public:
    QPushButton *pushBtnStop;
    QPushButton *pushBtnReturnHome;
    QPushButton *pushBtnCancel;
    QWebView *webView;
    QPushButton *pushButton;
    QPushButton *pushBtnFinish;

    void setupUi(QWidget *MapExecution)
    {
        if (MapExecution->objectName().isEmpty())
            MapExecution->setObjectName(QStringLiteral("MapExecution"));
        MapExecution->resize(1512, 978);
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
        MapExecution->setPalette(palette);
        pushBtnStop = new QPushButton(MapExecution);
        pushBtnStop->setObjectName(QStringLiteral("pushBtnStop"));
        pushBtnStop->setGeometry(QRect(1150, 820, 121, 51));
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
        pushBtnReturnHome = new QPushButton(MapExecution);
        pushBtnReturnHome->setObjectName(QStringLiteral("pushBtnReturnHome"));
        pushBtnReturnHome->setGeometry(QRect(850, 820, 121, 51));
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
        pushBtnCancel = new QPushButton(MapExecution);
        pushBtnCancel->setObjectName(QStringLiteral("pushBtnCancel"));
        pushBtnCancel->setGeometry(QRect(1300, 820, 121, 51));
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
        webView = new QWebView(MapExecution);
        webView->setObjectName(QStringLiteral("webView"));
        webView->setGeometry(QRect(120, 70, 1331, 711));
        webView->setUrl(QUrl(QStringLiteral("about:blank")));
        pushButton = new QPushButton(MapExecution);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(20, 30, 75, 23));
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
        pushBtnFinish = new QPushButton(MapExecution);
        pushBtnFinish->setObjectName(QStringLiteral("pushBtnFinish"));
        pushBtnFinish->setGeometry(QRect(1000, 820, 121, 51));
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

        retranslateUi(MapExecution);
        QObject::connect(pushBtnFinish, SIGNAL(clicked()), MapExecution, SLOT(finishClicked()));
        QObject::connect(pushBtnReturnHome, SIGNAL(clicked()), MapExecution, SLOT(returnHomeClicked()));
        QObject::connect(pushBtnCancel, SIGNAL(clicked()), MapExecution, SLOT(cancelClicked()));

        QMetaObject::connectSlotsByName(MapExecution);
    } // setupUi

    void retranslateUi(QWidget *MapExecution)
    {
        MapExecution->setWindowTitle(QApplication::translate("MapExecution", "Form", 0));
        pushBtnStop->setText(QApplication::translate("MapExecution", "Stop", 0));
        pushBtnReturnHome->setText(QApplication::translate("MapExecution", "Return home", 0));
        pushBtnCancel->setText(QApplication::translate("MapExecution", "Cancel", 0));
        pushButton->setText(QApplication::translate("MapExecution", "Back", 0));
        pushBtnFinish->setText(QApplication::translate("MapExecution", "Finish", 0));
    } // retranslateUi

};

namespace Ui {
    class MapExecution: public Ui_MapExecution {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAPEXECUTION_H
