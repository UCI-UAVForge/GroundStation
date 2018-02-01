#-------------------------------------------------
#
# Project created by QtCreator 2018-02-01T13:59:41
#
#-------------------------------------------------

QT       -= core gui

TARGET = lz4_dummy
TEMPLATE = lib
##CONFIG += staticlib
#CONFIG += recurse
#lz4_dummy.depends = lib/lz4.c
#lz4_dummy.recurse_target = true
##LIBS+=-L..
#SOURCES += \
#    lib/lz4.c \
#    lib/lz4hc.c

#HEADERS += \
#    lib/lz4.h \
#    lib/lz4hc.h
#lz4_dummy.commands = echo $$PWD

QMAKE_PRE_LINK = echo $$PWD && cd $$PWD && make -f $$PWD/Makefile
