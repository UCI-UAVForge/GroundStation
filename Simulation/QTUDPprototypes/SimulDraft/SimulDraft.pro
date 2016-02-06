QT += core
QT += network
QT += gui

TARGET = SimulDraft
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    server.cpp \
    groundstation.cpp

HEADERS += \
    server.h \
    groundstation.h


FORMS += \

RESOURCES +=


