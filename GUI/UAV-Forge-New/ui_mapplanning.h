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
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTableView>

QT_BEGIN_NAMESPACE

class Ui_MapPlanning
{
public:
    QPushButton *pushButton;
    QPushButton *pushButton_3;
    QPushButton *pushButton_2;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QTableView *tableView;
    QPushButton *pushButton_6;
    QWebView *webView;

    void setupUi(QDialog *MapPlanning)
    {
        if (MapPlanning->objectName().isEmpty())
            MapPlanning->setObjectName(QStringLiteral("MapPlanning"));
        MapPlanning->resize(1366, 768);
        pushButton = new QPushButton(MapPlanning);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(30, 20, 81, 21));
        pushButton_3 = new QPushButton(MapPlanning);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(220, 20, 91, 21));
        pushButton_2 = new QPushButton(MapPlanning);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(120, 20, 91, 21));
        pushButton_4 = new QPushButton(MapPlanning);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(320, 20, 91, 21));
        pushButton_5 = new QPushButton(MapPlanning);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(400, 60, 31, 23));
        tableView = new QTableView(MapPlanning);
        tableView->setObjectName(QStringLiteral("tableView"));
        tableView->setGeometry(QRect(30, 90, 411, 311));
        pushButton_6 = new QPushButton(MapPlanning);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setGeometry(QRect(490, 421, 131, 41));
        webView = new QWebView(MapPlanning);
        webView->setObjectName(QStringLiteral("webView"));
        webView->setGeometry(QRect(470, 90, 800, 650));
        webView->setUrl(QUrl(QStringLiteral("about:blank")));

        retranslateUi(MapPlanning);

        QMetaObject::connectSlotsByName(MapPlanning);
    } // setupUi

    void retranslateUi(QDialog *MapPlanning)
    {
        MapPlanning->setWindowTitle(QApplication::translate("MapPlanning", "Dialog", 0));
        pushButton->setText(QApplication::translate("MapPlanning", "File", 0));
        pushButton_3->setText(QApplication::translate("MapPlanning", "View", 0));
        pushButton_2->setText(QApplication::translate("MapPlanning", "Edit", 0));
        pushButton_4->setText(QApplication::translate("MapPlanning", "Tools", 0));
        pushButton_5->setText(QApplication::translate("MapPlanning", "+", 0));
        pushButton_6->setText(QApplication::translate("MapPlanning", "Execute", 0));
    } // retranslateUi

};

namespace Ui {
    class MapPlanning: public Ui_MapPlanning {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAPPLANNING_H
