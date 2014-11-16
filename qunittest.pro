# -------------------------------------------------
# Project created by hand
# -------------------------------------------------
QT += testlib
QT += core
QT += gui declarative
QT += widgets
TARGET = qunittest
CONFIG += console
CONFIG -= app_bundle
TEMPLATE = app
SOURCES += qunittest.cpp \
    cqueue.c \
    cqtest.cpp \
    testit.cpp \
    mainwindow.cpp
HEADERS += qunittest.h \
    cqueue.h \
    cqtest.h \
    testit.h \
    mainwindow.h

FORMS += mainwindow.ui
