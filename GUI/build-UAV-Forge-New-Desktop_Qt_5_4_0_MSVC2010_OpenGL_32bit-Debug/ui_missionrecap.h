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
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QPlainTextEdit>
#include <QtWidgets/QPushButton>
<<<<<<< .merge_file_a01612
#include <QtWidgets/QSlider>
=======
>>>>>>> .merge_file_a01972
#include <QtWidgets/QWidget>
#include <qvideowidget.h>

QT_BEGIN_NAMESPACE

class Ui_MissionRecap
{
public:
    QFrame *frame;
    QPlainTextEdit *plainTextEdit;
    QFrame *frame_2;
    QPlainTextEdit *plainTextEdit_2;
    QFrame *frame_3;
    QPlainTextEdit *plainTextEdit_3;
    QFrame *frame_4;
    QVideoWidget *VideoWidget;
    QFrame *frame_5;
    QPushButton *pushButton;
    QPushButton *playButton;
    QPushButton *stopButton;
<<<<<<< .merge_file_a01612
    QPushButton *openFileButton;
    QSlider *horizontalSlider;
=======
    QPushButton *stopButton_2;
>>>>>>> .merge_file_a01972
    QPushButton *newMission;
    QPushButton *redoMission;
    QPushButton *replayMission;
    QPushButton *backButton;

    void setupUi(QWidget *MissionRecap)
    {
        if (MissionRecap->objectName().isEmpty())
            MissionRecap->setObjectName(QStringLiteral("MissionRecap"));
        MissionRecap->resize(1366, 768);
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
        frame = new QFrame(MissionRecap);
        frame->setObjectName(QStringLiteral("frame"));
<<<<<<< .merge_file_a01612
        frame->setGeometry(QRect(280, 90, 341, 191));
=======
        frame->setGeometry(QRect(210, 80, 341, 191));
>>>>>>> .merge_file_a01972
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
        plainTextEdit = new QPlainTextEdit(frame);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(10, 10, 321, 171));
        frame_2 = new QFrame(MissionRecap);
        frame_2->setObjectName(QStringLiteral("frame_2"));
<<<<<<< .merge_file_a01612
        frame_2->setGeometry(QRect(280, 310, 341, 191));
=======
        frame_2->setGeometry(QRect(210, 290, 341, 191));
>>>>>>> .merge_file_a01972
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
        plainTextEdit_2 = new QPlainTextEdit(frame_2);
        plainTextEdit_2->setObjectName(QStringLiteral("plainTextEdit_2"));
        plainTextEdit_2->setGeometry(QRect(10, 10, 321, 171));
        frame_3 = new QFrame(MissionRecap);
        frame_3->setObjectName(QStringLiteral("frame_3"));
<<<<<<< .merge_file_a01612
        frame_3->setGeometry(QRect(650, 90, 341, 191));
=======
        frame_3->setGeometry(QRect(580, 80, 341, 191));
>>>>>>> .merge_file_a01972
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
        plainTextEdit_3->setGeometry(QRect(10, 10, 321, 171));
        frame_4 = new QFrame(MissionRecap);
        frame_4->setObjectName(QStringLiteral("frame_4"));
<<<<<<< .merge_file_a01612
        frame_4->setGeometry(QRect(650, 310, 341, 191));
=======
        frame_4->setGeometry(QRect(580, 290, 341, 191));
>>>>>>> .merge_file_a01972
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
<<<<<<< .merge_file_a01612
        VideoWidget->setGeometry(QRect(10, 10, 321, 171));
        frame_5 = new QFrame(MissionRecap);
        frame_5->setObjectName(QStringLiteral("frame_5"));
        frame_5->setGeometry(QRect(240, 60, 781, 511));
=======
        VideoWidget->setGeometry(QRect(9, 10, 321, 171));
        frame_5 = new QFrame(MissionRecap);
        frame_5->setObjectName(QStringLiteral("frame_5"));
        frame_5->setGeometry(QRect(180, 60, 781, 481));
>>>>>>> .merge_file_a01972
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
<<<<<<< .merge_file_a01612
        pushButton->setGeometry(QRect(650, 460, 101, 31));
=======
        pushButton->setGeometry(QRect(640, 440, 101, 31));
>>>>>>> .merge_file_a01972
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
<<<<<<< .merge_file_a01612
        playButton->setGeometry(QRect(410, 460, 101, 31));
=======
        playButton->setGeometry(QRect(490, 440, 101, 31));
>>>>>>> .merge_file_a01972
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
<<<<<<< .merge_file_a01612
        stopButton->setGeometry(QRect(530, 460, 101, 31));
=======
        stopButton->setGeometry(QRect(380, 440, 101, 31));
>>>>>>> .merge_file_a01972
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
<<<<<<< .merge_file_a01612
        openFileButton = new QPushButton(frame_5);
        openFileButton->setObjectName(QStringLiteral("openFileButton"));
        openFileButton->setGeometry(QRect(280, 460, 101, 31));
        openFileButton->setStyleSheet(QLatin1String(" QPushButton { \n"
=======
        stopButton_2 = new QPushButton(frame_5);
        stopButton_2->setObjectName(QStringLiteral("stopButton_2"));
        stopButton_2->setGeometry(QRect(260, 440, 101, 31));
        stopButton_2->setStyleSheet(QLatin1String(" QPushButton { \n"
>>>>>>> .merge_file_a01972
"background-color: #434A54;\n"
"color: \"#ffffff\"; \n"
"border-radius: 10px;\n"
"font-weight: bold;\n"
"border: none; \n"
"}\n"
" QPushButton:pressed {\n"
"     background-color: #656D78\n"
" }"));
<<<<<<< .merge_file_a01612
        horizontalSlider = new QSlider(frame_5);
        horizontalSlider->setObjectName(QStringLiteral("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(410, 440, 341, 19));
        horizontalSlider->setOrientation(Qt::Horizontal);
        newMission = new QPushButton(MissionRecap);
        newMission->setObjectName(QStringLiteral("newMission"));
        newMission->setGeometry(QRect(670, 610, 151, 41));
=======
        newMission = new QPushButton(MissionRecap);
        newMission->setObjectName(QStringLiteral("newMission"));
        newMission->setGeometry(QRect(824, 560, 111, 31));
>>>>>>> .merge_file_a01972
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
<<<<<<< .merge_file_a01612
        redoMission->setGeometry(QRect(450, 610, 151, 41));
=======
        redoMission->setGeometry(QRect(700, 560, 111, 31));
>>>>>>> .merge_file_a01972
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
<<<<<<< .merge_file_a01612
        replayMission->setGeometry(QRect(870, 610, 151, 41));
=======
        replayMission->setGeometry(QRect(560, 560, 121, 31));
>>>>>>> .merge_file_a01972
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
<<<<<<< .merge_file_a01612
        backButton->setGeometry(QRect(240, 610, 151, 41));
=======
        backButton->setGeometry(QRect(180, 20, 75, 23));
>>>>>>> .merge_file_a01972
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
        frame_5->raise();
        frame->raise();
        frame_2->raise();
        frame_3->raise();
        frame_4->raise();
        newMission->raise();
        redoMission->raise();
        replayMission->raise();
        backButton->raise();

        retranslateUi(MissionRecap);
        QObject::connect(replayMission, SIGNAL(clicked()), MissionRecap, SLOT(replayMissionClicked()));

        QMetaObject::connectSlotsByName(MissionRecap);
    } // setupUi

    void retranslateUi(QWidget *MissionRecap)
    {
        MissionRecap->setWindowTitle(QApplication::translate("MissionRecap", "Form", 0));
<<<<<<< .merge_file_a01612
        plainTextEdit->setPlainText(QApplication::translate("MissionRecap", "         Graphical Representation of Results", 0));
        plainTextEdit_2->setPlainText(QApplication::translate("MissionRecap", "         Graphical Representation of Results", 0));
        plainTextEdit_3->setPlainText(QApplication::translate("MissionRecap", "                                Text Results", 0));
        pushButton->setText(QApplication::translate("MissionRecap", "Save", 0));
        playButton->setText(QApplication::translate("MissionRecap", "Play/Pause", 0));
        stopButton->setText(QApplication::translate("MissionRecap", "Stop", 0));
        openFileButton->setText(QApplication::translate("MissionRecap", "Open File", 0));
=======
        plainTextEdit->setPlainText(QApplication::translate("MissionRecap", "Graphical Representation of Results", 0));
        plainTextEdit_2->setPlainText(QApplication::translate("MissionRecap", "Graphical Representation of Results", 0));
        plainTextEdit_3->setPlainText(QApplication::translate("MissionRecap", "Text Results", 0));
        pushButton->setText(QApplication::translate("MissionRecap", "Save Results", 0));
        playButton->setText(QApplication::translate("MissionRecap", "Play", 0));
        stopButton->setText(QApplication::translate("MissionRecap", "Stop", 0));
        stopButton_2->setText(QApplication::translate("MissionRecap", "Stop", 0));
>>>>>>> .merge_file_a01972
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
