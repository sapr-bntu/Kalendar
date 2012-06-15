#-------------------------------------------------
#
# Project created by QtCreator 2012-06-14T20:15:52
#
#-------------------------------------------------

QT       += network opengl  script scripttools svg webkit xml xmlpatterns multimedia qt3support testlib  core gui sql

TARGET = tst_testbasetest
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += tst_testbasetest.cpp \
    ../dialog.cpp
DEFINES += SRCDIR=\\\"$$PWD/\\\"

HEADERS += \
    ../dialog.h


