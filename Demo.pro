#-------------------------------------------------
#
# Project created by QtCreator 2014-01-08T17:40:08
#
#-------------------------------------------------

QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Demo
TEMPLATE = app


SOURCES += main.cpp\
        window.cpp \
    glwidget.cpp \
    window2.cpp \
    glwidget2.cpp \
    window3.cpp \
    glwidget3.cpp

HEADERS  += window.h \
    glwidget.h \
    window2.h \
    glwidget2.h \
    window3.h \
    glwidget3.h

RESOURCES += \
    shaders.qrc

OTHER_FILES += \
    basic.frag \
    basic.vert \
    basic2.vert

FORMS +=
