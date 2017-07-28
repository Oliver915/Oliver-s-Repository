CONFIG += create_prl staticlib
CONFIG += c++11

QT += core gui opengl

TEMPLATE = lib

TARGET = gui

DESTDIR =$$OUT_PWD/../lib

INCLUDEPATH += \
    $$PWD/../protobuf

LIBS += \
    -losg -losgDB -losgViewer -losgGA -losgUtil -losgQt \
    -lOpenThreads -losgAnimation -losgText -losgSim \
    -L$$OUT_PWD/../lib -lprotobuf

HEADERS += \
    uav.h \
    createhud_viewpoint.h \
    myhandler.h \
    findnodevisitor.h \
    viewerqt.h \
    adapterwidget.h \
    mainwindow.h \
    mps_coordinate.pb.h

SOURCES += \
    uav.cpp \
    createhud_viewpoint.cpp \
    myhandler.cpp \
    findnodevisitor.cpp \
    viewerqt.cpp \
    adapterwidget.cpp \
    mainwindow.cpp \
    mps_coordinate.pb.cc

FORMS += \
    mainwindow.ui
