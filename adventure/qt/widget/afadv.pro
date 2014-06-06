QT       += core gui

# Uncomment the next line to enable debug build
#CONFIG += debug

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Adventure
TEMPLATE = app

SOURCES = main.cpp \
        mainwindow.cpp \
        gameengine.cpp

HEADERS  += mainwindow.h gameengine.h

FORMS    += mainwindow.ui

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

OTHER_FILES += \
    android/AndroidManifest.xml
