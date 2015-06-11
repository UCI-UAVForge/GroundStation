/********************************************************************************
** Form generated from reading UI file 'mapplanning.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>

QT_BEGIN_NAMESPACE

class Ui_MapPlanning
{
public:
    QGridLayout *gridLayout;
    QPushButton *backButton;
    QWebView *webView;
    QPushButton *executeButton;
    QPushButton *updateTableButton;
    QPushButton *clearTableButton;
    QPushButton *clearMapButton;
    QPushButton *deleteButton;
    QPushButton *addButton;
    QTableView *tableView;

    void setupUi(QDialog *MapPlanning)
    {
        if (MapPlanning->objectName().isEmpty())
            MapPlanning->setObjectName(QStringLiteral("MapPlanning"));
        MapPlanning->resize(1360, 1097);
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
        gridLayout = new QGridLayout(MapPlanning);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        backButton = new QPushButton(MapPlanning);
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

        webView = new QWebView(MapPlanning);
        webView->setObjectName(QStringLiteral("webView"));
        webView->setUrl(QUrl(QStringLiteral("about:blank")));

        gridLayout->addWidget(webView, 1, 1, 1, 6);

        executeButton = new QPushButton(MapPlanning);
        executeButton->setObjectName(QStringLiteral("executeButton"));
        executeButton->setStyleSheet(QLatin1String(" QPushButton { \n"
"background-color: \"#CCD1D9\"; \n"
"color: \"#434A54\"; \n"
"border-radius: 10px;\n"
"font-weight: bold;\n"
"border: none; \n"
"}\n"
" QPushButton:pressed {\n"
"     background-color: #E6E9ED\n"
" }"));

        gridLayout->addWidget(executeButton, 2, 1, 1, 1);

        updateTableButton = new QPushButton(MapPlanning);
        updateTableButton->setObjectName(QStringLiteral("updateTableButton"));
        updateTableButton->setStyleSheet(QLatin1String(" QPushButton { \n"
"background-color: \"#CCD1D9\"; \n"
"color: \"#434A54\"; \n"
"border-radius: 10px;\n"
"font-weight: bold;\n"
"border: none; \n"
"}\n"
" QPushButton:pressed {\n"
"     background-color: #E6E9ED\n"
" }"));

        gridLayout->addWidget(updateTableButton, 2, 2, 1, 1);

        clearTableButton = new QPushButton(MapPlanning);
        clearTableButton->setObjectName(QStringLiteral("clearTableButton"));
        clearTableButton->setStyleSheet(QLatin1String(" QPushButton { \n"
"background-color: \"#CCD1D9\"; \n"
"color: \"#434A54\"; \n"
"border-radius: 10px;\n"
"font-weight: bold;\n"
"border: none; \n"
"}\n"
" QPushButton:pressed {\n"
"     background-color: #E6E9ED\n"
" }"));

        gridLayout->addWidget(clearTableButton, 2, 3, 1, 1);

        clearMapButton = new QPushButton(MapPlanning);
        clearMapButton->setObjectName(QStringLiteral("clearMapButton"));
        clearMapButton->setStyleSheet(QLatin1String(" QPushButton { \n"
"background-color: \"#CCD1D9\"; \n"
"color: \"#434A54\"; \n"
"border-radius: 10px;\n"
"font-weight: bold;\n"
"border: none; \n"
"}\n"
" QPushButton:pressed {\n"
"     background-color: #E6E9ED\n"
" }"));

        gridLayout->addWidget(clearMapButton, 2, 4, 1, 1);

        deleteButton = new QPushButton(MapPlanning);
        deleteButton->setObjectName(QStringLiteral("deleteButton"));
        deleteButton->setStyleSheet(QLatin1String(" QPushButton { \n"
"background-color: \"#CCD1D9\"; \n"
"color: \"#434A54\"; \n"
"border-radius: 4px;\n"
"font-weight: bold;\n"
"border: none; \n"
"}\n"
" QPushButton:pressed {\n"
"     background-color: #E6E9ED\n"
" }"));

        gridLayout->addWidget(deleteButton, 2, 5, 1, 1);

        addButton = new QPushButton(MapPlanning);
        addButton->setObjectName(QStringLiteral("addButton"));
        addButton->setStyleSheet(QLatin1String(" QPushButton { \n"
"background-color: \"#CCD1D9\"; \n"
"color: \"#434A54\"; \n"
"border-radius: 4px;\n"
"font-weight: bold;\n"
"border: none; \n"
"}\n"
" QPushButton:pressed {\n"
"     background-color: #E6E9ED\n"
" }"));

        gridLayout->addWidget(addButton, 2, 6, 1, 1);

        tableView = new QTableView(MapPlanning);
        tableView->setObjectName(QStringLiteral("tableView"));

        gridLayout->addWidget(tableView, 3, 1, 1, 6);


        retranslateUi(MapPlanning);

        QMetaObject::connectSlotsByName(MapPlanning);
    } // setupUi

    void retranslateUi(QDialog *MapPlanning)
    {
        MapPlanning->setWindowTitle(QApplication::translate("MapPlanning", "Dialog", 0));
        backButton->setText(QApplication::translate("MapPlanning", "Back", 0));
        executeButton->setText(QApplication::translate("MapPlanning", "Execute", 0));
        updateTableButton->setText(QApplication::translate("MapPlanning", "Update Table", 0));
        clearTableButton->setText(QApplication::translate("MapPlanning", "Clear Table", 0));
        clearMapButton->setText(QApplication::translate("MapPlanning", "Clear Map", 0));
        deleteButton->setText(QApplication::translate("MapPlanning", "-", 0));
        addButton->setText(QApplication::translate("MapPlanning", "+", 0));
    } // retranslateUi

};

namespace Ui {
    class MapPlanning: public Ui_MapPlanning {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAPPLANNING_H
