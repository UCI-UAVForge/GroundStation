/********************************************************************************
** Form generated from reading UI file 'mapplanning.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAPPLANNING_H
#define UI_MAPPLANNING_H

#include <QtCore/QVariant>
#include <QtWebKitWidgets/QWebView>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>

QT_BEGIN_NAMESPACE

class Ui_MapPlanning
{
public:
    QPushButton *AddRow;
    QTableView *tableView;
    QPushButton *Execute;
    QWebView *webView;
    QPushButton *RemoveRow;
    QPushButton *Update;
    QPushButton *Back;
    QPushButton *clearTable;
    QPushButton *clearMap;

    void setupUi(QDialog *MapPlanning)
    {
        if (MapPlanning->objectName().isEmpty())
            MapPlanning->setObjectName(QStringLiteral("MapPlanning"));
        MapPlanning->resize(1522, 919);
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
        MapPlanning->setPalette(palette);
        AddRow = new QPushButton(MapPlanning);
        AddRow->setObjectName(QStringLiteral("AddRow"));
        AddRow->setGeometry(QRect(1450, 520, 31, 31));
        AddRow->setStyleSheet(QLatin1String(" QPushButton { \n"
"background-color: \"#CCD1D9\"; \n"
"color: \"#434A54\"; \n"
"border-radius: 4px;\n"
"font-weight: bold;\n"
"border: none; \n"
"}\n"
" QPushButton:pressed {\n"
"     background-color: #E6E9ED\n"
" }"));
        AddRow->setFlat(false);
        tableView = new QTableView(MapPlanning);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(110, 560, 1391, 311));
        Execute = new QPushButton(MapPlanning);
        Execute->setObjectName(QStringLiteral("Execute"));
        Execute->setGeometry(QRect(120, 510, 101, 41));
        Execute->setStyleSheet(QLatin1String(" QPushButton { \n"
"background-color: \"#CCD1D9\"; \n"
"color: \"#434A54\"; \n"
"border-radius: 10px;\n"
"font-weight: bold;\n"
"border: none; \n"
"}\n"
" QPushButton:pressed {\n"
"     background-color: #E6E9ED\n"
" }"));
        webView = new QWebView(MapPlanning);
        webView->setObjectName(QStringLiteral("webView"));
        webView->setGeometry(QRect(110, 50, 1391, 431));
        webView->setUrl(QUrl(QStringLiteral("about:blank")));
        RemoveRow = new QPushButton(MapPlanning);
        RemoveRow->setObjectName(QStringLiteral("RemoveRow"));
        RemoveRow->setGeometry(QRect(1410, 520, 31, 31));
        RemoveRow->setStyleSheet(QLatin1String(" QPushButton { \n"
"background-color: \"#CCD1D9\"; \n"
"color: \"#434A54\"; \n"
"border-radius: 4px;\n"
"font-weight: bold;\n"
"border: none; \n"
"}\n"
" QPushButton:pressed {\n"
"     background-color: #E6E9ED\n"
" }"));
        Update = new QPushButton(MapPlanning);
        Update->setObjectName(QStringLiteral("Update"));
        Update->setGeometry(QRect(250, 510, 121, 41));
        Update->setStyleSheet(QLatin1String(" QPushButton { \n"
"background-color: \"#CCD1D9\"; \n"
"color: \"#434A54\"; \n"
"border-radius: 10px;\n"
"font-weight: bold;\n"
"border: none; \n"
"}\n"
" QPushButton:pressed {\n"
"     background-color: #E6E9ED\n"
" }"));
        Back = new QPushButton(MapPlanning);
        Back->setObjectName(QStringLiteral("Back"));
        Back->setGeometry(QRect(30, 20, 75, 23));
        Back->setStyleSheet(QLatin1String(" QPushButton { \n"
"background-color: \"#CCD1D9\"; \n"
"color: \"#434A54\"; \n"
"border-radius: 10px;\n"
"font-weight: bold;\n"
"border: none; \n"
"}\n"
" QPushButton:pressed {\n"
"     background-color: #E6E9ED\n"
" }"));
        clearTable = new QPushButton(MapPlanning);
        clearTable->setObjectName(QStringLiteral("clearTable"));
        clearTable->setGeometry(QRect(400, 510, 101, 41));
        clearTable->setStyleSheet(QLatin1String(" QPushButton { \n"
"background-color: \"#CCD1D9\"; \n"
"color: \"#434A54\"; \n"
"border-radius: 10px;\n"
"font-weight: bold;\n"
"border: none; \n"
"}\n"
" QPushButton:pressed {\n"
"     background-color: #E6E9ED\n"
" }"));
        clearMap = new QPushButton(MapPlanning);
        clearMap->setObjectName(QStringLiteral("clearMap"));
        clearMap->setGeometry(QRect(530, 510, 101, 41));
        clearMap->setStyleSheet(QLatin1String(" QPushButton { \n"
"background-color: \"#CCD1D9\"; \n"
"color: \"#434A54\"; \n"
"border-radius: 10px;\n"
"font-weight: bold;\n"
"border: none; \n"
"}\n"
" QPushButton:pressed {\n"
"     background-color: #E6E9ED\n"
" }"));

        retranslateUi(MapPlanning);

        QMetaObject::connectSlotsByName(MapPlanning);
    } // setupUi

    void retranslateUi(QDialog *MapPlanning)
    {
        MapPlanning->setWindowTitle(QApplication::translate("MapPlanning", "Dialog", 0));
        AddRow->setText(QApplication::translate("MapPlanning", "+", 0));
        Execute->setText(QApplication::translate("MapPlanning", "Execute", 0));
        RemoveRow->setText(QApplication::translate("MapPlanning", "-", 0));
        Update->setText(QApplication::translate("MapPlanning", "Update Table", 0));
        Back->setText(QApplication::translate("MapPlanning", "Back", 0));
        clearTable->setText(QApplication::translate("MapPlanning", "Clear Table", 0));
        clearMap->setText(QApplication::translate("MapPlanning", "Clear Path", 0));
    } // retranslateUi

};

namespace Ui {
    class MapPlanning: public Ui_MapPlanning {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAPPLANNING_H
