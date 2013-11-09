#-------------------------------------------------
#
# Project created by QtCreator 2013-11-09T09:33:26
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = tpv_qtperf
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    testwidget.cpp

HEADERS  += mainwindow.h \
    testwidget.h

FORMS    += mainwindow.ui \
    testwidget.ui

OTHER_FILES +=

RESOURCES += \
    resources.qrc
