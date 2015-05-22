/********************************************************************************
** Form generated from reading UI file 'missionrecap.ui'
**
** Created by: Qt User Interface Compiler version 5.4.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MISSIONRECAP_H
#define UI_MISSIONRECAP_H

#include <QtCore/QVariant>
#include <QtWebKitWidgets/QWebView>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>
#include <qcustomplot.h>
#include "qvideowidget.h"

QT_BEGIN_NAMESPACE

class Ui_MissionRecap
{
public:
    QFrame *frame_5;
    QPushButton *pushButton;
    QPushButton *playButton;
    QPushButton *stopButton;
    QPushButton *openFileButton;
    QFrame *frame_2;
    QCustomPlot *customPlot;
    QFrame *frame_4;
    QVideoWidget *VideoWidget;
    QFrame *frame_3;
    QPlainTextEdit *plainTextEdit_3;
    QFrame *frame;
    QWebView *webView;
    QSlider *horizontalSlider;
    QComboBox *comboBox;
    QTextBrowser *textBrowser;
    QTextBrowser *textBrowser_2;
    QTextBrowser *textBrowser_3;
    QComboBox *comboBox_2;
    QComboBox *comboBox_3;
    QPushButton *newMission;
    QPushButton *redoMission;
    QPushButton *replayMission;
    QPushButton *backButton;

    void setupUi(QWidget *MissionRecap)
    {
        if (MissionRecap->objectName().isEmpty())
            MissionRecap->setObjectName(QStringLiteral("MissionRecap"));
        MissionRecap->resize(1666, 919);
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
        MissionRecap->setPalette(palette);
        frame_5 = new QFrame(MissionRecap);
        frame_5->setObjectName(QStringLiteral("frame_5"));
        frame_5->setGeometry(QRect(0, 60, 1601, 751));
        frame_5->setStyleSheet(QLatin1String(" QFrame, QLabel, QToolTip {\n"
"     border: 2px solid grey;\n"
"     border-radius: 4px;\n"
"     padding: 2px;\n"
"	 color: #434A54;\n"
"	 font-weight: bold;\n"
"     background-color: #CCD1D9;\n"
" }"));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        pushButton = new QPushButton(frame_5);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(1490, 340, 101, 31));
        pushButton->setStyleSheet(QLatin1String(" QPushButton { \n"
"background-color: #434A54;\n"
"color: \"#ffffff\"; \n"
"border-radius: 10px;\n"
"font-weight: bold;\n"
"border: none; \n"
"}\n"
" QPushButton:pressed {\n"
"     background-color: #656D78\n"
" }"));
        playButton = new QPushButton(frame_5);
        playButton->setObjectName(QStringLiteral("playButton"));
        playButton->setGeometry(QRect(1030, 340, 101, 31));
        playButton->setStyleSheet(QLatin1String(" QPushButton { \n"
"background-color: #434A54;\n"
"color: \"#ffffff\"; \n"
"border-radius: 10px;\n"
"font-weight: bold;\n"
"border: none; \n"
"}\n"
" QPushButton:pressed {\n"
"     background-color: #656D78\n"
" }"));
        stopButton = new QPushButton(frame_5);
        stopButton->setObjectName(QStringLiteral("stopButton"));
        stopButton->setGeometry(QRect(1240, 340, 101, 31));
        stopButton->setStyleSheet(QLatin1String(" QPushButton { \n"
"background-color: #434A54;\n"
"color: \"#ffffff\"; \n"
"border-radius: 10px;\n"
"font-weight: bold;\n"
"border: none; \n"
"}\n"
" QPushButton:pressed {\n"
"     background-color: #656D78\n"
" }"));
        openFileButton = new QPushButton(frame_5);
        openFileButton->setObjectName(QStringLiteral("openFileButton"));
        openFileButton->setGeometry(QRect(810, 340, 101, 31));
        openFileButton->setStyleSheet(QLatin1String(" QPushButton { \n"
"background-color: #434A54;\n"
"color: \"#ffffff\"; \n"
"border-radius: 10px;\n"
"font-weight: bold;\n"
"border: none; \n"
"}\n"
" QPushButton:pressed {\n"
"     background-color: #656D78\n"
" }"));
        frame_2 = new QFrame(frame_5);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setGeometry(QRect(10, 400, 781, 331));
        frame_2->setStyleSheet(QLatin1String(" QFrame, QLabel, QToolTip {\n"
"     border: 2px solid grey;\n"
"     border-radius: 4px;\n"
"     padding: 2px;\n"
"	 color: #434A54;\n"
"	 font-weight: bold;\n"
"     background-color: #CCD1D9;\n"
" }"));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        customPlot = new QCustomPlot(frame_2);
        customPlot->setObjectName(QStringLiteral("customPlot"));
        customPlot->setGeometry(QRect(10, 10, 761, 311));
        frame_4 = new QFrame(frame_5);
        frame_4->setObjectName(QStringLiteral("frame_4"));
        frame_4->setGeometry(QRect(810, 10, 781, 311));
        frame_4->setStyleSheet(QLatin1String(" QFrame, QLabel, QToolTip {\n"
"     border: 2px solid grey;\n"
"     border-radius: 4px;\n"
"     padding: 2px;\n"
"	 color: #434A54;\n"
"	 font-weight: bold;\n"
"     background-color: #CCD1D9;\n"
" }"));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        VideoWidget = new QVideoWidget(frame_4);
        VideoWidget->setObjectName(QStringLiteral("VideoWidget"));
        VideoWidget->setGeometry(QRect(10, 10, 761, 291));
        frame_3 = new QFrame(frame_5);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setGeometry(QRect(810, 400, 781, 331));
        frame_3->setStyleSheet(QLatin1String(" QFrame, QLabel, QToolTip {\n"
"     border: 2px solid grey;\n"
"     border-radius: 4px;\n"
"     padding: 2px;\n"
"	 color: #434A54;\n"
"	 font-weight: bold;\n"
"     background-color: #CCD1D9;\n"
" }"));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        plainTextEdit_3 = new QPlainTextEdit(frame_3);
        plainTextEdit_3->setObjectName(QStringLiteral("plainTextEdit_3"));
        plainTextEdit_3->setGeometry(QRect(10, 10, 761, 311));
        frame = new QFrame(frame_5);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(10, 10, 781, 331));
        frame->setStyleSheet(QLatin1String(" QFrame, QLabel, QToolTip {\n"
"     border: 2px solid grey;\n"
"     border-radius: 4px;\n"
"     padding: 2px;\n"
"	 color: #434A54;\n"
"	 font-weight: bold;\n"
"     background-color: #CCD1D9;\n"
" }"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        webView = new QWebView(frame);
        webView->setObjectName(QStringLiteral("webView"));
        webView->setGeometry(QRect(10, 10, 761, 311));
        webView->setUrl(QUrl(QStringLiteral("about:blank")));
        horizontalSlider = new QSlider(frame_5);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(810, 320, 771, 21));
        horizontalSlider->setPageStep(1);
        horizontalSlider->setOrientation(Qt::Horizontal);
        horizontalSlider->setTickPosition(QSlider::TicksBothSides);
        horizontalSlider->setTickInterval(5000);
        comboBox = new QComboBox(frame_5);
        comboBox->setObjectName(QStringLiteral("comboBox"));
        comboBox->setGeometry(QRect(120, 360, 131, 31));
        textBrowser = new QTextBrowser(frame_5);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->setGeometry(QRect(20, 360, 91, 31));
        textBrowser_2 = new QTextBrowser(frame_5);
        textBrowser_2->setObjectName(QStringLiteral("textBrowser_2"));
        textBrowser_2->setGeometry(QRect(270, 360, 101, 31));
        textBrowser_3 = new QTextBrowser(frame_5);
        textBrowser_3->setObjectName(QStringLiteral("textBrowser_3"));
        textBrowser_3->setGeometry(QRect(540, 360, 101, 31));
        comboBox_2 = new QComboBox(frame_5);
        comboBox_2->setObjectName(QStringLiteral("comboBox_2"));
        comboBox_2->setGeometry(QRect(380, 360, 131, 31));
        comboBox_3 = new QComboBox(frame_5);
        comboBox_3->setObjectName(QStringLiteral("comboBox_3"));
        comboBox_3->setGeometry(QRect(650, 360, 131, 31));
        newMission = new QPushButton(MissionRecap);
        newMission->setObjectName(QStringLiteral("newMission"));
        newMission->setGeometry(QRect(1260, 830, 151, 41));
        newMission->setStyleSheet(QLatin1String(" QPushButton { \n"
"background-color: \"#CCD1D9\"; \n"
"color: \"#434A54\"; \n"
"border-radius: 10px;\n"
"font-weight: bold;\n"
"border: none; \n"
"}\n"
" QPushButton:pressed {\n"
"     background-color: #E6E9ED\n"
" }"));
        redoMission = new QPushButton(MissionRecap);
        redoMission->setObjectName(QStringLiteral("redoMission"));
        redoMission->setGeometry(QRect(1080, 830, 151, 41));
        redoMission->setStyleSheet(QLatin1String(" QPushButton { \n"
"background-color: \"#CCD1D9\"; \n"
"color: \"#434A54\"; \n"
"border-radius: 10px;\n"
"font-weight: bold;\n"
"border: none; \n"
"}\n"
" QPushButton:pressed {\n"
"     background-color: #E6E9ED\n"
" }"));
        replayMission = new QPushButton(MissionRecap);
        replayMission->setObjectName(QStringLiteral("replayMission"));
        replayMission->setGeometry(QRect(1440, 830, 151, 41));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush1);
        QBrush brush2(QColor(204, 209, 217, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush2);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush1);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush2);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush2);
        replayMission->setPalette(palette1);
        replayMission->setStyleSheet(QLatin1String(" QPushButton { \n"
"background-color: \"#CCD1D9\"; \n"
"color: \"#434A54\"; \n"
"border-radius: 10px;\n"
"font-weight: bold;\n"
"border: none; \n"
"}\n"
" QPushButton:pressed {\n"
"     background-color: #E6E9ED\n"
" }"));
        backButton = new QPushButton(MissionRecap);
        backButton->setObjectName(QStringLiteral("backButton"));
        backButton->setGeometry(QRect(20, 20, 75, 23));
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

        retranslateUi(MissionRecap);
        QObject::connect(replayMission, SIGNAL(clicked()), MissionRecap, SLOT(replayMissionClicked()));

        QMetaObject::connectSlotsByName(MissionRecap);
    } // setupUi

    void retranslateUi(QWidget *MissionRecap)
    {
        MissionRecap->setWindowTitle(QApplication::translate("MissionRecap", "Form", 0));
        pushButton->setText(QApplication::translate("MissionRecap", "Save", 0));
        playButton->setText(QApplication::translate("MissionRecap", "Play/Pause", 0));
        stopButton->setText(QApplication::translate("MissionRecap", "Stop", 0));
        openFileButton->setText(QApplication::translate("MissionRecap", "Open File", 0));
        plainTextEdit_3->setPlainText(QApplication::translate("MissionRecap", "                                         Status", 0));
        comboBox->clear();
        comboBox->insertItems(0, QStringList()
         << QApplication::translate("MissionRecap", "Line", 0)
         << QApplication::translate("MissionRecap", "Bar", 0)
         << QApplication::translate("MissionRecap", "Pie", 0)
        );
        textBrowser->setHtml(QApplication::translate("MissionRecap", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:600; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-size:8pt;\">Graph Type:</span></p></body></html>", 0));
        textBrowser_2->setHtml(QApplication::translate("MissionRecap", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:600; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">X Parameters:</p></body></html>", 0));
        textBrowser_3->setHtml(QApplication::translate("MissionRecap", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'MS Shell Dlg 2'; font-size:8.25pt; font-weight:600; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">Y Parameters:</p></body></html>", 0));
        comboBox_2->clear();
        comboBox_2->insertItems(0, QStringList()
         << QApplication::translate("MissionRecap", "Hours", 0)
         << QApplication::translate("MissionRecap", "Distance", 0)
        );
        comboBox_3->clear();
        comboBox_3->insertItems(0, QStringList()
         << QApplication::translate("MissionRecap", "Work Completed", 0)
         << QApplication::translate("MissionRecap", "Power", 0)
        );
        newMission->setText(QApplication::translate("MissionRecap", "New Mission", 0));
        redoMission->setText(QApplication::translate("MissionRecap", "Redo Mission", 0));
        replayMission->setText(QApplication::translate("MissionRecap", "Replay Mission", 0));
        backButton->setText(QApplication::translate("MissionRecap", "Back", 0));
    } // retranslateUi

};

namespace Ui {
    class MissionRecap: public Ui_MissionRecap {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MISSIONRECAP_H
