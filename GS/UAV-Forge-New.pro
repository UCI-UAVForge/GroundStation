#-------------------------------------------------
#
# Project created by QtCreator 2014-11-02T13:10:01
#
#-------------------------------------------------

QT       += core \
            gui \
            multimedia \
            multimediawidgets \
            network
QT       += svg


QT       += webkit webkitwidgets
QT       += webengine webenginewidgets

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
    messagebox.cpp \
    ActionPacket.cpp \
    InfoPacket.cpp \
    TelemetryPacket.cpp \
    Packet.cpp \
    digitalclock.cpp \
    mapvalidator.cpp \
    serverqueue.cpp \
    mission.cpp \
    flightpath.cpp \
    maprecap.cpp \
    AckPacket.cpp

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
    messagebox.h \
    digitalclock.h \
    mapvalidator.h \
    serverqueue.h \
    mission.h \
    flightpath.h \
    maprecap.h \
    Packet.h \
    AckPacket.h \
    ActionPacket.h \
    InfoPacket.h \
    TelemetryPacket.h

FORMS    += mainwindow.ui \
    options.ui \
    mapplanning.ui \
    mapexecution.ui \
    missionrecap.ui \
    tutorial.ui \
    popwindowmp.ui \
    connectiondialog.ui \
    maprecap.ui

OTHER_FILES +=

RESOURCES += \
    Resources.qrc

DISTFILES +=
