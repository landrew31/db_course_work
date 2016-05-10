#-------------------------------------------------
#
# Project created by QtCreator 2016-04-01T19:52:17
#
#-------------------------------------------------

QT       += core gui
QT       += core sql
CONFIG   += console
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Supermarket
TEMPLATE = app


SOURCES += main.cpp \
    mainwindow.cpp \
    dialogentry.cpp \
    db_setup.cpp \
    messagebox.cpp

HEADERS  += \
    mainwindow.h \
    dialogentry.h \
    db_setup.h \
    messagebox.h

FORMS    += \
    mainwindow.ui \
    dialogentry.ui
