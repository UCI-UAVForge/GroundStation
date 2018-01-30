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

win32:CONFIG(release, debug|release): LIBS += -L$$OUT_PWD/../flann/release/ -llz4
else:win32:CONFIG(debug, debug|release): LIBS += -L$$OUT_PWD/../flann/debug/ -llz4
else:unix: LIBS += -L$$OUT_PWD/../flann/ -llz4

INCLUDEPATH += $$PWD/../flann
DEPENDPATH += $$PWD/../flann

win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../flann/release/liblz4.a
else:win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../flann/debug/liblz4.a
else:win32:!win32-g++:CONFIG(release, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../flann/release/lz4.lib
else:win32:!win32-g++:CONFIG(debug, debug|release): PRE_TARGETDEPS += $$OUT_PWD/../flann/debug/lz4.lib
else:unix: PRE_TARGETDEPS += $$OUT_PWD/../flann/liblz4.a
