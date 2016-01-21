QT += core gui
QT += widgets
QT += network

TARGET = SimulDraft2
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    groundstation.cpp \
    ActionPacket.cpp \
    InfoPacket.cpp \
    Packet.cpp \
    TelemetryPacket.cpp

HEADERS += \
    groundstation.h \
    ackpacket.h \
    actionpacket.h \
    infopacket.h \
    packet.h \
    telemetrypacket.h

FORMS += \
    dialog.ui

DISTFILES += \
    SimulDraft2.pro.user

CONFIG += c++11
