#-------------------------------------------------
#
# Project created by QtCreator 2014-12-19T21:20:51
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Projet_System
TEMPLATE = app


SOURCES += main.cpp\
    group.cpp \
    proc.cpp \
    scheduler.cpp \
    utilisateur.cpp \
    graphpainter.cpp \
    mainwidget.cpp \
    creationfichierconfigurationdialog.cpp \
    creationproc.cpp \
    planing.cpp \
    utile.cpp

HEADERS  += \
    group.h \
    proc.h \
    scheduler.h \
    utilisateur.h \
    graphpainter.h \
    mainwidget.h \
    creationfichierconfigurationdialog.h \
    creationproc.h \
    planing.h \
    utile.h

FORMS    += mainwindow.ui
