#-------------------------------------------------
#
# Project created by QtCreator 2016-02-10T09:42:32
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = spammer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
		inireader.cpp \
		qobjecthelper.cpp \
        qlogger.cpp

HEADERS  += mainwindow.h \
		inireader.h \
		qobjecthelper.h \
        qlogger.h \
        test.h \
        tools.h \
        templates.h

FORMS    += mainwindow.ui
