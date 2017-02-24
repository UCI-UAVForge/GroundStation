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
QT       += sql

QT       += webengine
QT       += webenginewidgets
QT       += webchannel
QT       += websockets
QT       += widgets


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

#CONFIG += console

CONFIG += c++11
#win32{
#    LIBS += -lws2_32
#}
macx {
    QMAKE_MAC_SDK = macosx10.12
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
    gscontrolpanel.cpp \
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
    qttabtest.cpp \
    mainmdidisplay.cpp \
    missionplanningwindow.cpp \
    dbmanager.cpp \
    mapwidget.cpp \
    websocketclientwrapper.cpp \
    websockettransport.cpp \
    tablewidget.cpp \
    #statuswidget.cpp \
    timerwidget.cpp \
    missionstatuswindow.cpp

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
    gscontrolpanel.h \
    gsserver.h \
    qcustomplot.h\
    networklistener.h \
    connectiondialog.h \
    messagebox.h \
    actionpacket.h \
    infopacket.h \
    telemetrypacket.h \
    ackpacket.h \
    packet.h \
    digitalclock.h \
    mapvalidator.h \
    serverqueue.h \
    mission.h \
    flightpath.h \
    maprecap.h \
    qttabtest.h \
    mainmdidisplay.h \
    missionplanningwindow.h \
    dbmanager.h \
    mapwidget.h \
    websocketclientwrapper.h \
    websockettransport.h \
    dialog.h \
    tablewidget.h \
    #statuswidget.h \
    timerwidget.h \
    missionstatuswindow.h

FORMS    += mainwindow.ui \
    options.ui \
    mapplanning.ui \
    mapexecution.ui \
    missionrecap.ui \
    tutorial.ui \
    popwindowmp.ui \
    gscontrolpanel.ui \
    connectiondialog.ui \
    maprecap.ui \
    qttabtest.ui \
    mainmdidisplay.ui \
    dialog.ui \
    missionstatuswindow.ui

OTHER_FILES +=

#Uncomment this line, clean the build, run qmake, and then rebuild to use the old GUI.
#DEFINES += OLD_GUI

RESOURCES += \
    Resources.qrc

#DISTFILES += \
#    res/html/mapsPlanningGoogle.html
