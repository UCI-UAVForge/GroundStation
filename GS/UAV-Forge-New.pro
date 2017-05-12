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

SOURCES += \
    main.cpp \
    GUI/*.cpp \
    Network/*.cpp \
    Util/*.cpp \
    Database/*.cpp \

HEADERS  += \
    GUI/*.h \
    Network/*.h \
    Util/*.h \
    Database/*.h \

FORMS    += \
    GUI/*.ui \

OTHER_FILES +=

RESOURCES += \
    Resources.qrc
