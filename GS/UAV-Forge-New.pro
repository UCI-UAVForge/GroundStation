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
    $$files(Util/*.c, false) \
    $$files(Util/*.cpp, false) \
    $$files(Network/*.cpp, false) \
    $$files(Database/*.cpp, false)


HEADERS  += \
    $$files(GUI/*.h, false) \
    $$files(Util/*.h, false) \
    $$files(Util/*.hpp, false) \
    $$files(Network/*.h, false) \
    $$files(Database/*.h, false)


FORMS    += \
    $$files(GUI/*.ui, false) \

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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/3rdparty/flann/release/ -llz4
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/3rdparty/flann/debug/ -llz4
else:unix: LIBS += -L$$OUT_PWD/3rdparty/flann/ -llz4

INCLUDEPATH += $$PWD/3rdparty/flann
DEPENDPATH += $$PWD/3rdparty/flann

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/3rdparty/flann/release/liblz4.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/3rdparty/flann/debug/liblz4.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/3rdparty/flann/release/lz4.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/3rdparty/flann/debug/lz4.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/3rdparty/flann/liblz4.a
