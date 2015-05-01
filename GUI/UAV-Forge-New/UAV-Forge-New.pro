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

QT       += core gui multimedia multimediawidgets
QT       += webkit webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
#CONFIG += console

CONFIG += c++11
#LIBS += -lws2_32
TARGET = UAV-Forge-New
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
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
    jsonobject.cpp
QMAKE_MAC_SDK = macosx10.9
HEADERS  += mainwindow.h \
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
    jsonobject.h

FORMS    += mainwindow.ui \
    mapplanning.ui \
    mapexecution.ui \
    missionrecap.ui \
    tutorial.ui \
    popwindowmp.ui

OTHER_FILES +=

RESOURCES += \
    Resources.qrc
