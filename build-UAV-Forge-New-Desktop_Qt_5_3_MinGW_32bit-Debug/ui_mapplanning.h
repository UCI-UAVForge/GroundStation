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
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MapPlanning
{
public:
    QFrame *frame;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;
    QComboBox *comboBox;
    QComboBox *comboBox_2;
    QComboBox *comboBox_3;
    QComboBox *comboBox_4;
    QComboBox *comboBox_5;
    QComboBox *comboBox_6;
    QComboBox *comboBox_7;
    QPushButton *pushButton_6;
    QPushButton *pushButton;
    QPushButton *pushButton_3;
    QPushButton *pushButton_2;
    QPushButton *pushButton_4;
    QFrame *frame_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QPushButton *pushButton_5;

    void setupUi(QDialog *MapPlanning)
    {
        if (MapPlanning->objectName().isEmpty())
            MapPlanning->setObjectName(QStringLiteral("MapPlanning"));
        MapPlanning->resize(1137, 475);
        frame = new QFrame(MapPlanning);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(40, 80, 221, 321));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        scrollArea_2 = new QScrollArea(frame);
        scrollArea_2->setObjectName(QStringLiteral("scrollArea_2"));
        scrollArea_2->setGeometry(QRect(0, 0, 221, 321));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QStringLiteral("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 219, 319));
        comboBox = new QComboBox(scrollAreaWidgetContents_2);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(10, 20, 151, 20));
        comboBox_2 = new QComboBox(scrollAreaWidgetContents_2);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));
        comboBox_2->setGeometry(QRect(10, 70, 151, 20));
        comboBox_3 = new QComboBox(scrollAreaWidgetContents_2);
        comboBox_3->setObjectName(QStringLiteral("comboBox_3"));
        comboBox_3->setGeometry(QRect(10, 110, 151, 20));
        comboBox_4 = new QComboBox(scrollAreaWidgetContents_2);
        comboBox_4->setObjectName(QStringLiteral("comboBox_4"));
        comboBox_4->setGeometry(QRect(10, 150, 151, 20));
        comboBox_5 = new QComboBox(scrollAreaWidgetContents_2);
        comboBox_5->setObjectName(QStringLiteral("comboBox_5"));
        comboBox_5->setGeometry(QRect(10, 270, 151, 20));
        comboBox_6 = new QComboBox(scrollAreaWidgetContents_2);
        comboBox_6->setObjectName(QStringLiteral("comboBox_6"));
        comboBox_6->setGeometry(QRect(10, 230, 151, 20));
        comboBox_7 = new QComboBox(scrollAreaWidgetContents_2);
        comboBox_7->setObjectName(QStringLiteral("comboBox_7"));
        comboBox_7->setGeometry(QRect(10, 190, 151, 20));
        pushButton_6 = new QPushButton(scrollAreaWidgetContents_2);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));
        pushButton_6->setGeometry(QRect(170, 20, 41, 23));
        scrollArea_2->setWidget(scrollAreaWidgetContents_2);
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
        frame_2 = new QFrame(MapPlanning);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setGeometry(QRect(450, 70, 481, 341));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        scrollArea = new QScrollArea(frame_2);
        scrollArea->setObjectName(QStringLiteral("scrollArea"));
        scrollArea->setGeometry(QRect(0, 0, 481, 341));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 479, 339));
        scrollArea->setWidget(scrollAreaWidgetContents);
        pushButton_5 = new QPushButton(MapPlanning);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(230, 50, 31, 23));

        retranslateUi(MapPlanning);

        QMetaObject::connectSlotsByName(MapPlanning);
    } // setupUi

    void retranslateUi(QDialog *MapPlanning)
    {
        MapPlanning->setWindowTitle(QApplication::translate("MapPlanning", "Dialog", 0));
        pushButton_6->setText(QApplication::translate("MapPlanning", "delete", 0));
        pushButton->setText(QApplication::translate("MapPlanning", "File", 0));
        pushButton_3->setText(QApplication::translate("MapPlanning", "View", 0));
        pushButton_2->setText(QApplication::translate("MapPlanning", "Edit", 0));
        pushButton_4->setText(QApplication::translate("MapPlanning", "Tools", 0));
        pushButton_5->setText(QApplication::translate("MapPlanning", "+", 0));
    } // retranslateUi

};

namespace Ui {
    class MapPlanning: public Ui_MapPlanning {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAPPLANNING_H
