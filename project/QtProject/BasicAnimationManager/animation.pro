QT += core
QT += gui opengl

CONFIG += c++11

TARGET = animation
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp

LIBS  += -losg -losgDB -losgUtil -losgViewer -losgGA -losgSim -losgAnimation -losgWidget
