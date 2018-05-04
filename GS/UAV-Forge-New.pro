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
QT       += serialport
QT       += positioning
QT       += quick


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
    $$files(Util/*.c, false) \
    $$files(Util/*.cpp, false) \
    $$files(Network/*.cpp, false) \
    $$files(Database/*.cpp, false) \

HEADERS  += \
    $$files(GUI/*.h, false) \
    $$files(Util/*.h, false) \
    $$files(Util/*.hpp, false) \
    $$files(Network/*.h, false) \
    $$files(Database/*.h, false) \

FORMS    += \
    $$files(GUI/*.ui, false)

OTHER_FILES +=

RESOURCES += \
    Resources.qrc

INCLUDEPATH += ardupilotmav/ardupilotmega/

DISTFILES +=

INCLUDEPATH += 3rdparty/

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/3rdparty/rrt/release/ -lrrt
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/3rdparty/rrt/debug/ -lrrt
else:unix: LIBS += -L$$OUT_PWD/3rdparty/rrt/ -lrrt

INCLUDEPATH += $$PWD/3rdparty/rrt
DEPENDPATH += $$PWD/3rdparty/rrt

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/3rdparty/rrt/release/librrt.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/3rdparty/rrt/debug/librrt.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/3rdparty/rrt/release/rrt.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/3rdparty/rrt/debug/rrt.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/3rdparty/rrt/librrt.a



win32 {
win32:contains(QMAKE_HOST.arch, x86_64):{
    #for win64
    LIBS += -L$$PWD/3rdparty/lz4/lib/dll64/ -lliblz4
} else {
    #for win32
    LIBS += -L$$PWD/3rdparty/lz4/lib/dll32/ -lliblz4
}
}
unix: LIBS += -L$$PWD/3rdparty/lz4/lib/ -llz4

INCLUDEPATH += $$PWD/3rdparty/lz4/lib/dll/
DEPENDPATH += $$PWD/3rdparty/lz4/lib/dll/

