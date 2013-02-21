QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ArtifactRandomizer
TEMPLATE = app

SOURCES += main.cpp \
    MainWidget.cpp \
    AboutDialog.cpp

HEADERS  += \
    MainWidget.h \
    AboutDialog.h
