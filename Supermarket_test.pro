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
    dialogentry.cpp \
    db_setup.cpp \
    messagebox.cpp \
    functions.cpp \
    hr_department.cpp \
    dialog_editpersinfo.cpp \
    sale_department.cpp

HEADERS  += \
    dialogentry.h \
    db_setup.h \
    messagebox.h \
    hr_department.h \
    dialog_editpersinfo.h \
    sale_department.h

FORMS    += \
    dialogentry.ui \
    hr_department.ui \
    dialogui_editpersinfo.ui \
    sale_department.ui
