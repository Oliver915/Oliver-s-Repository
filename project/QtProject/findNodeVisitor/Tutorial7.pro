TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG += qt

SOURCES += main.cpp \
    findnodevisitor.cpp

HEADERS += \
    findnodevisitor.h
QT += gui opengl
LIBS  +=  -losg -losgDB -losgViewer -losgGA -losgUtil -losgQt -lOpenThreads -losgAnimation -losgText -losgSim
