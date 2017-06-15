QT += core
QT += gui opengl

CONFIG += c++11

TARGET = map
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    creatnewmap.cpp

LIBS  += -losg -losgDB -losgViewer -losgGA -losgUtil
