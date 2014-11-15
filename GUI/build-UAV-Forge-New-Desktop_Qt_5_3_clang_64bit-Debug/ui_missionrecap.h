/********************************************************************************
** Form generated from reading UI file 'missionrecap.ui'
**
** Created by: Qt User Interface Compiler version 5.3.2
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
#include <QtWidgets/QWidget>

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
    QPlainTextEdit *plainTextEdit_4;
    QFrame *frame_5;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;

    void setupUi(QWidget *MissionRecap)
    {
        if (MissionRecap->objectName().isEmpty())
            MissionRecap->setObjectName(QStringLiteral("MissionRecap"));
        MissionRecap->resize(955, 587);
        frame = new QFrame(MissionRecap);
        frame->setObjectName(QStringLiteral("frame"));
        frame->setGeometry(QRect(210, 80, 341, 191));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        plainTextEdit = new QPlainTextEdit(frame);
        plainTextEdit->setObjectName(QStringLiteral("plainTextEdit"));
        plainTextEdit->setGeometry(QRect(10, 10, 321, 171));
        frame_2 = new QFrame(MissionRecap);
        frame_2->setObjectName(QStringLiteral("frame_2"));
        frame_2->setGeometry(QRect(210, 290, 341, 191));
        frame_2->setFrameShape(QFrame::StyledPanel);
        frame_2->setFrameShadow(QFrame::Raised);
        plainTextEdit_2 = new QPlainTextEdit(frame_2);
        plainTextEdit_2->setObjectName(QStringLiteral("plainTextEdit_2"));
        plainTextEdit_2->setGeometry(QRect(10, 10, 321, 171));
        frame_3 = new QFrame(MissionRecap);
        frame_3->setObjectName(QStringLiteral("frame_3"));
        frame_3->setGeometry(QRect(580, 80, 341, 191));
        frame_3->setFrameShape(QFrame::StyledPanel);
        frame_3->setFrameShadow(QFrame::Raised);
        plainTextEdit_3 = new QPlainTextEdit(frame_3);
        plainTextEdit_3->setObjectName(QStringLiteral("plainTextEdit_3"));
        plainTextEdit_3->setGeometry(QRect(10, 10, 321, 171));
        frame_4 = new QFrame(MissionRecap);
        frame_4->setObjectName(QStringLiteral("frame_4"));
        frame_4->setGeometry(QRect(580, 290, 341, 191));
        frame_4->setFrameShape(QFrame::StyledPanel);
        frame_4->setFrameShadow(QFrame::Raised);
        plainTextEdit_4 = new QPlainTextEdit(frame_4);
        plainTextEdit_4->setObjectName(QStringLiteral("plainTextEdit_4"));
        plainTextEdit_4->setGeometry(QRect(10, 10, 321, 171));
        frame_5 = new QFrame(MissionRecap);
        frame_5->setObjectName(QStringLiteral("frame_5"));
        frame_5->setGeometry(QRect(180, 60, 761, 461));
        frame_5->setFrameShape(QFrame::StyledPanel);
        frame_5->setFrameShadow(QFrame::Raised);
        pushButton = new QPushButton(frame_5);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(644, 430, 101, 23));
        pushButton_2 = new QPushButton(MissionRecap);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(824, 550, 111, 23));
        pushButton_3 = new QPushButton(MissionRecap);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(710, 550, 111, 23));
        pushButton_4 = new QPushButton(MissionRecap);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(590, 550, 121, 23));
        frame_5->raise();
        frame->raise();
        frame_2->raise();
        frame_3->raise();
        frame_4->raise();
        pushButton_2->raise();
        pushButton_3->raise();
        pushButton_4->raise();

        retranslateUi(MissionRecap);
        QObject::connect(pushButton_4, SIGNAL(clicked()), MissionRecap, SLOT(replayMissionClicked()));

        QMetaObject::connectSlotsByName(MissionRecap);
    } // setupUi

    void retranslateUi(QWidget *MissionRecap)
    {
        MissionRecap->setWindowTitle(QApplication::translate("MissionRecap", "Form", 0));
        plainTextEdit->setPlainText(QApplication::translate("MissionRecap", "Graphical Representation of Results", 0));
        plainTextEdit_2->setPlainText(QApplication::translate("MissionRecap", "Graphical Representation of Results", 0));
        plainTextEdit_3->setPlainText(QApplication::translate("MissionRecap", "Text Results", 0));
        plainTextEdit_4->setPlainText(QApplication::translate("MissionRecap", "Video Playback of Mission", 0));
        pushButton->setText(QApplication::translate("MissionRecap", "Save Results", 0));
        pushButton_2->setText(QApplication::translate("MissionRecap", "New Mission", 0));
        pushButton_3->setText(QApplication::translate("MissionRecap", "Redo Mission", 0));
        pushButton_4->setText(QApplication::translate("MissionRecap", "Replay Mission", 0));
    } // retranslateUi

};

namespace Ui {
    class MissionRecap: public Ui_MissionRecap {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MISSIONRECAP_H
