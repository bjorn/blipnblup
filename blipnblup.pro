#-------------------------------------------------
#
# Project created by QtCreator 2014-04-15T19:04:32
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

QMAKE_CXXFLAGS += -std=c++1y
TARGET = blipnblup
TEMPLATE = app


SOURCES += main.cpp\
    gamewidget.cpp \
    bubble.cpp \
    gameobject.cpp \
    player.cpp \
    wasp.cpp \
    foe.cpp

HEADERS  += \
    gamewidget.h \
    bubble.h \
    gameobject.h \
    player.h \
    wasp.h \
    foe.h

FORMS    +=

RESOURCES += \
    blipnblup.qrc
