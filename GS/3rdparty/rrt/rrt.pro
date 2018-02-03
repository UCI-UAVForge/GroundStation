#-------------------------------------------------
#
# Project created by QtCreator 2018-01-29T20:24:55
#
#-------------------------------------------------

TARGET = rrt
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++11
CONFIG -= qt

SOURCES += \
    $$files(*.cpp, false) \
    $$files(2dplane/*.cpp, false) \
    $$files(planning/*.cpp, false)

HEADERS += \
    $$files(*.hpp, false) \
    $$files(2dplane/*.hpp, false) \
    $$files(planning/*.hpp, false)

#LIBS += -L/usr/local/Cellar/lz4/1.8.1.2/lib -llz4
INCLUDEPATH += ../

win32:CONFIG(release, debug|release): LIBS += -L$$PWD/../lz4/lib/release/ -llz4
else:win32:CONFIG(debug, debug|release): LIBS += -L$$PWD/../lz4/lib/debug/ -llz4
else:unix: LIBS += -L$$PWD/../lz4/lib/ -llz4

INCLUDEPATH += $$PWD/../lz4
DEPENDPATH += $$PWD/../lz4

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lz4/lib/release/liblz4.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lz4/lib/debug/liblz4.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$PWD/../lz4/lib/release/lz4.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$PWD/../lz4/lib/debug/lz4.lib
else:unix: PRE_TARGETDEPS += $$PWD/../lz4/lib/liblz4.a
