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

unix|win32: LIBS += -L$$PWD/../lz4/lib/ -lliblz4

INCLUDEPATH += $$PWD/../lz4/lib/
DEPENDPATH += $$PWD/../lz4/lib/
