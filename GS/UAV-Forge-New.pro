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
QT       += widgets
QT       += quickwidgets
QT       += charts
QT       += serialport
QT       += positioning


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets printsupport

#CONFIG += console

CONFIG += c++11
#win32{
#    LIBS += -lws2_32
#}
macx {
    QMAKE_MAC_SDK = macosx10.12
}

TEMPLATE = app
TARGET = UAV-Forge-New

#TEMPLATE = app
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
    $$files(Util/*.c, false) \


HEADERS  += \
    $$files(GUI/*.h, false) \
    $$files(Util/*.h, false) \
    $$files(Util/*.hpp, false) \
    $$files(Network/*.h, false) \
    $$files(Database/*.h, false) \


FORMS    += \
    $$files(GUI/*.ui, false) \

OTHER_FILES +=

RESOURCES += \
    Resources.qrc

INCLUDEPATH += ardupilotmav/ardupilotmega/


DISTFILES +=


win32:CONFIG(release, debug|release): LIBS += -L$$PWD/components/release/ -lcomponents
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/components/debug/ -lcomponents
else:unix: LIBS += -L$$PWD/components/ -lcomponents

INCLUDEPATH += $$PWD/components
DEPENDPATH += $$PWD/components

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/components/release/libcomponents.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/components/debug/libcomponents.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/components/release/components.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/components/debug/components.lib
else:unix: PRE_TARGETDEPS += $$PWD/components/libcomponents.a
