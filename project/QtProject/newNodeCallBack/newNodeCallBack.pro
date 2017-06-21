QT += core
QT += gui

CONFIG += c++11

TARGET = newNodeCallBack
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    newnodecallback.cpp

LIBS  +=  -losg -losgDB -losgViewer -losgGA -losgUtil -losgQt -lOpenThreads -losgAnimation

HEADERS += \
    newnodecallback.h
