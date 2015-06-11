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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MapExecution
{
public:
    QGridLayout *gridLayout;
    QPushButton *backButton;
    QWebView *webView;
    QPushButton *returnHomeButton;
    QPushButton *finishButton;
    QPushButton *stopButton;
    QPushButton *cancelButton;
    QTableView *tableView;

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
        gridLayout = new QGridLayout(MapExecution);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        backButton = new QPushButton(MapExecution);
        backButton->setObjectName(QStringLiteral("backButton"));
        backButton->setStyleSheet(QLatin1String(" QPushButton { \n"
"background-color: \"#CCD1D9\"; \n"
"color: \"#434A54\"; \n"
"border-radius: 10px;\n"
"font-weight: bold;\n"
"border: none; \n"
"}\n"
" QPushButton:pressed {\n"
"     background-color: #E6E9ED\n"
" }"));

        gridLayout->addWidget(backButton, 0, 0, 1, 1);

        webView = new QWebView(MapExecution);
        webView->setObjectName(QStringLiteral("webView"));
        webView->setUrl(QUrl(QStringLiteral("about:blank")));

        gridLayout->addWidget(webView, 1, 1, 1, 4);

        returnHomeButton = new QPushButton(MapExecution);
        returnHomeButton->setObjectName(QStringLiteral("returnHomeButton"));
        returnHomeButton->setStyleSheet(QLatin1String(" QPushButton { \n"
"background-color: \"#CCD1D9\"; \n"
"color: \"#434A54\"; \n"
"border-radius: 10px;\n"
"font-weight: bold;\n"
"border: none; \n"
"}\n"
" QPushButton:pressed {\n"
"     background-color: #E6E9ED\n"
" }"));

        gridLayout->addWidget(returnHomeButton, 2, 1, 1, 1);

        finishButton = new QPushButton(MapExecution);
        finishButton->setObjectName(QStringLiteral("finishButton"));
        finishButton->setStyleSheet(QLatin1String(" QPushButton { \n"
"background-color: \"#CCD1D9\"; \n"
"color: \"#434A54\"; \n"
"border-radius: 10px;\n"
"font-weight: bold;\n"
"border: none; \n"
"}\n"
" QPushButton:pressed {\n"
"     background-color: #E6E9ED\n"
" }"));

        gridLayout->addWidget(finishButton, 2, 2, 1, 1);

        stopButton = new QPushButton(MapExecution);
        stopButton->setObjectName(QStringLiteral("stopButton"));
        stopButton->setStyleSheet(QLatin1String(" QPushButton { \n"
"background-color: \"#CCD1D9\"; \n"
"color: \"#434A54\"; \n"
"border-radius: 10px;\n"
"font-weight: bold;\n"
"border: none; \n"
"}\n"
" QPushButton:pressed {\n"
"     background-color: #E6E9ED\n"
" }"));

        gridLayout->addWidget(stopButton, 2, 3, 1, 1);

        cancelButton = new QPushButton(MapExecution);
        cancelButton->setObjectName(QStringLiteral("cancelButton"));
        cancelButton->setStyleSheet(QLatin1String(" QPushButton { \n"
"background-color: \"#CCD1D9\"; \n"
"color: \"#434A54\"; \n"
"border-radius: 10px;\n"
"font-weight: bold;\n"
"border: none; \n"
"}\n"
" QPushButton:pressed {\n"
"     background-color: #E6E9ED\n"
" }"));

        gridLayout->addWidget(cancelButton, 2, 4, 1, 1);

        tableView = new QTableView(MapExecution);
        tableView->setObjectName(QStringLiteral("tableView"));

        gridLayout->addWidget(tableView, 3, 1, 1, 1);


        retranslateUi(MapExecution);

        QMetaObject::connectSlotsByName(MapExecution);
    } // setupUi

    void retranslateUi(QWidget *MapExecution)
    {
        MapExecution->setWindowTitle(QApplication::translate("MapExecution", "Form", 0));
        backButton->setText(QApplication::translate("MapExecution", "Back", 0));
        returnHomeButton->setText(QApplication::translate("MapExecution", "Return home", 0));
        finishButton->setText(QApplication::translate("MapExecution", "Finish", 0));
        stopButton->setText(QApplication::translate("MapExecution", "Stop", 0));
        cancelButton->setText(QApplication::translate("MapExecution", "Cancel", 0));
    } // retranslateUi

};

namespace Ui {
    class MapExecution: public Ui_MapExecution {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAPEXECUTION_H
