QT += core
QT += gui opengl

CONFIG += c++11

TARGET = zoomInGlider
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    gliderzoomin.cpp

LIBS  +=  -losg -losgDB -losgViewer -losgGA -losgUtil -losgQt -lOpenThreads
