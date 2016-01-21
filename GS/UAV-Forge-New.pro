#-------------------------------------------------
#
# Project created by QtCreator 2014-11-02T13:10:01
#
#-------------------------------------------------

QT       += core \
            gui \
            webkitwidgets \
            multimedia \
            multimediawidgets
QT       += svg

QT       += core gui multimedia multimediawidgets
QT       += webkit webkitwidgets


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport
#CONFIG += console

CONFIG += c++11
win32{
    LIBS += -lws2_32
}
TARGET = UAV-Forge-New
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    options.cpp \
    mapplanning.cpp \
    tablemodel.cpp \
    mapexecution.cpp \
    missionrecap.cpp \
    tutorial.cpp \
    popwindowmp.cpp \
    qcomboboxdelegate.cpp \
    videoplayer.cpp \
    gsserver.cpp \
    gsclient.cpp \
    qcustomplot.cpp\
    networklistener.cpp \
    connectiondialog.cpp \
    ActionPacket.cpp \
    InfoPacket.cpp \
    messagebox.cpp \
    Packet.cpp \
    TelemetryPacket.cpp
QMAKE_MAC_SDK = macosx10.9
HEADERS  += mainwindow.h \
    options.h \
    mapplanning.h \
    tablemodel.h \
    mapexecution.h \
    missionrecap.h \
    tutorial.h \
    popwindowmp.h \
    qcomboboxdelegate.h \
    videoplayer.h \
    net.h \
    gsserver.h \
    gsclient.h \
    qcustomplot.h\
    networklistener.h \
    connectiondialog.h \
    ackpacket.h \
    infopacket.h \
    messagebox.h \
    packet.h \
    telemetrypacket.h \
    actionpacket.h

FORMS    += mainwindow.ui \
    options.ui \
    mapplanning.ui \
    mapexecution.ui \
    missionrecap.ui \
    tutorial.ui \
    popwindowmp.ui \
    connectiondialog.ui

OTHER_FILES +=

RESOURCES += \
    Resources.qrc

DISTFILES +=
