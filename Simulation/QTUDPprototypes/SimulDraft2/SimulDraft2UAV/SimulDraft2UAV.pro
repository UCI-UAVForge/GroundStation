#-------------------------------------------------
#
# Project created by QtCreator 2015-10-30T16:20:15
#
#-------------------------------------------------

QT       += core gui
QT += network
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SimulDraft2UAV
TEMPLATE = app


SOURCES += main.cpp \
    uav.cpp \
    ActionPacket.cpp \
    InfoPacket.cpp \
    Packet.cpp \
    TelemetryPacket.cpp

HEADERS  += \
    uav.h \
    ackpacket.h \
    actionpacket.h \
    infopacket.h \
    packet.h \
    telemetrypacket.h

FORMS    += dialog.ui

DISTFILES += \
    SimulDraft2UAV.pro.user
CONFIG += c++11
