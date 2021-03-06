#-------------------------------------------------
#
# Project created by QtCreator 2016-04-01T19:52:17
#
#-------------------------------------------------

QT       += core gui
QT       += core sql
QT       += printsupport
CONFIG   -= console
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
    sale_department.cpp \
    dialog_actions.cpp \
    dialog_contractors.cpp \
    dialog_programs.cpp \
    dialog_program_info.cpp \
    dialog_card_info.cpp \
    dialog_createskill.cpp \
    dialog_good_types.cpp \
    dialog_editposition.cpp \
    dialog_good_actions_info.cpp \
    dialog_removevacancy.cpp \
    dialog_openvacancy.cpp \
    dialog_showpositinfo.cpp \
    dialog_showstaffprofile.cpp \
    dialog_changeposition.cpp \
    dialog_addstaff.cpp \
    dialog_firestaff.cpp \
    dialog_buy_goods.cpp \
    dialog_staffabsence.cpp \
    dialog_addstaffabsence.cpp \
    dialog_createabstype.cpp


HEADERS  += \
    dialogentry.h \
    db_setup.h \
    messagebox.h \
    hr_department.h \
    dialog_editpersinfo.h \
    sale_department.h \
    dialog_actions.h \
    dialog_contractors.h \
    dialog_programs.h \
    dialog_program_info.h \
    dialog_card_info.h \
    dialog_createskill.h \
    functions.h \
    dialog_good_types.h \
    dialog_editposition.h \
    dialog_good_actions_info.h \
    dialog_removevacancy.h \
    dialog_openvacancy.h \
    dialog_showpositinfo.h \
    dialog_showstaffprofile.h \
    dialog_changeposition.h \
    dialog_addstaff.h \
    dialog_firestaff.h \
    dialog_buy_goods.h \
    dialog_staffabsence.h \
    dialog_addstaffabsence.h \
    dialog_createabstype.h


FORMS    += \
    dialogentry.ui \
    hr_department.ui \
    dialogui_editpersinfo.ui \
    sale_department.ui \
    dialog_actions.ui \
    dialog_contractors.ui \
    dialog_programs.ui \
    dialog_program_info.ui \
    dialog_card_info.ui \
    dialog_createskill.ui \
    dialog_good_types.ui \
    dialog_editposition.ui \
    dialog_good_actions_info.ui \
    dialog_removevacancy.ui \
    dialog_openvacancy.ui \
    dialog_showpositinfo.ui \
    dialog_showstaffprofile.ui \
    dialog_changeposition.ui \
    dialog_addstaff.ui \
    dialog_firestaff.ui \
    dialog_buy_goods.ui \
    dialog_staffabsence.ui \
    dialog_addstaffabsence.ui \
    dialog_createabstype.ui
