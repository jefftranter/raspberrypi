QT       += core gui

# Uncomment the next line to enable debug build
CONFIG += debug

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = afadv
TEMPLATE = app

SOURCES = main.cpp \
        mainwindow.cpp \
        gameengine.cpp

HEADERS  += mainwindow.h gameengine.h

FORMS    += mainwindow.ui
