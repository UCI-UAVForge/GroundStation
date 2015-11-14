QT += core gui
QT += widgets
QT += network

TARGET = SimulDraft2
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    groundstation.cpp

HEADERS += \
    groundstation.h

