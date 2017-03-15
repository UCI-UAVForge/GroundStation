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

#PRECOMPILED_HEADER = qcustomplot.h

SOURCES += main.cpp\
    tablemodel.cpp \
    qcomboboxdelegate.cpp \
    gsserver.cpp \
    gscontrolpanel.cpp \
    qcustomplot.cpp\
    networklistener.cpp \
    messagebox.cpp \
    ActionPacket.cpp \
    InfoPacket.cpp \
    TelemetryPacket.cpp \
    Packet.cpp \
    #digitalclock.cpp \
    mapvalidator.cpp \
    serverqueue.cpp \
    mission.cpp \
    flightpath.cpp \
    #qttabtest.cpp \
    mainmdidisplay.cpp \
    missionplanningwindow.cpp \
    dbmanager.cpp \
    mapwidget.cpp \
    websocketclientwrapper.cpp \
    websockettransport.cpp \
    tablewidget.cpp \
    statuswidget.cpp \
    graphwidget.cpp \
    timerwidget.cpp \
    missionstatuswindow.cpp #\
    #mainwindow.cpp \
    #options.cpp \
    #mapplanning.cpp \
    #mapexecution.cpp \
    #missionrecap.cpp \
    #tutorial.cpp \
    #popwindowmp.cpp \
    #videoplayer.cpp \
    #connectiondialog.cpp \
    #maprecap.cpp \

HEADERS  += tablemodel.h \
    qcomboboxdelegate.h \
    net.h \
    gscontrolpanel.h \
    gsserver.h \
    qcustomplot.h\
    networklistener.h \
    messagebox.h \
    actionpacket.h \
    infopacket.h \
    telemetrypacket.h \
    ackpacket.h \
    packet.h \
    #digitalclock.h \
    mapvalidator.h \
    serverqueue.h \
    mission.h \
    flightpath.h \
    #qttabtest.h \
    mainmdidisplay.h \
    missionplanningwindow.h \
    dbmanager.h \
    mapwidget.h \
    websocketclientwrapper.h \
    websockettransport.h \
    #dialog.h \
    tablewidget.h \
    graphwidget.h \
    statuswidget.h \
    timerwidget.h \
    missionstatuswindow.h #\
    #mainwindow.h \
    #options.h \
    #mapplanning.h \
    #mapexecution.h \
    #missionrecap.h \
    #tutorial.h \
    #popwindowmp.h \
    #videoplayer.h \
    #connectiondialog.h \
    #maprecap.h \

FORMS    += gscontrolpanel.ui \
    #qttabtest.ui \
    mainmdidisplay.ui \
    graphwidget.ui\
    missionstatuswindow.ui #\
    #mainwindow.ui \
    #options.ui \
    #mapplanning.ui \
    #mapexecution.ui \
    #missionrecap.ui \
    #tutorial.ui \
    #popwindowmp.ui \
    #connectiondialog.ui \
    #maprecap.ui \
    #dialog.ui \

OTHER_FILES +=

RESOURCES += \
    Resources.qrc
