#-------------------------------------------------
#
# Project created by QtCreator 2014-11-02T13:10:01
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets
QT       += webkit webkitwidgets
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

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
    uavcon.cpp
QMAKE_MAC_SDK = macosx10.9
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
    uavcon.h \
    net.h

FORMS    += mainwindow.ui \
    options.ui \
    mapplanning.ui \
    mapexecution.ui \
    missionrecap.ui \
    tutorial.ui \
    popwindowmp.ui

OTHER_FILES +=

RESOURCES += \
    Resources.qrc
