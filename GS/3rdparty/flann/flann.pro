#-------------------------------------------------
#
# Project created by QtCreator 2018-01-29T20:33:06
#
#-------------------------------------------------

TARGET = lz4
TEMPLATE = lib
CONFIG += staticlib
CONFIG += c++11
CONFIG -= qt

SOURCES += \
    ext/lz4.c \
    ext/lz4hc.c
HEADERS += \
    ext/lz4.h \
    ext/lz4hc.h

INCLUDEPATH += ../
