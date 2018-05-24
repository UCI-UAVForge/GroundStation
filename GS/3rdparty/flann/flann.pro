#-------------------------------------------------
#
# Project created by QtCreator 2018-01-29T20:33:06
#
#-------------------------------------------------

TARGET = liblz4
TEMPLATE = app
CONFIG += c++11
#CONFIG += staticlib
CONFIG -= qt

SOURCES += \
    ext/lz4.c \
    ext/lz4hc.c

HEADERS += \
    ext/lz4hc.h \
    ext/lz4.h
#INCLUDEPATH += ./
