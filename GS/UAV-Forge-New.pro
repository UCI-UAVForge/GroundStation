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
QT       += quickwidgets


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

INCLUDEPATH += \
    $$PWD/GUI \
    $$PWD/Network \
    $$PWD/Util \
    $$PWD/Database

SOURCES += \
    main.cpp \
    $$files(GUI/*.cpp, false) \
    $$files(Util/*.cpp, false) \
    $$files(Network/*.cpp, false) \
    $$files(Database/*.cpp, false) \

HEADERS  += \
    $$files(GUI/*.h, false) \
    $$files(Util/*.h, false) \
    $$files(Network/*.h, false) \
    $$files(Database/*.h, false) \

FORMS    += \
    $$files(GUI/*.ui, false) \

OTHER_FILES +=

RESOURCES += \
    Resources.qrc

INCLUDEPATH += ardupilotmav/ardupilotmega/

DISTFILES +=
