QT += core
QT += gui opengl

CONFIG += c++11

TARGET = UAVsimplefight
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    adapterwidget.cpp \
    viewerqt.cpp \
    transform.cpp

LIBS  +=  -losg -losgDB -losgViewer -losgGA -losgUtil -losgQt -lOpenThreads -losgAnimation

HEADERS += \
    adapterwidget.h \
    viewerqt.h \
    transform.h


