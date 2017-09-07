TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle

QT += core gui opengl

LIBS += \
    -losg -losgDB -losgViewer -losgGA -losgUtil -losgQt \
    -lOpenThreads -losgAnimation -losgText -losgSim \

SOURCES += main.cpp \
    followupdater.cpp

HEADERS += \
    followupdater.h
