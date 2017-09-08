CONFIG += create_prl staticlib c++11

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
    myhandler.h \
    viewerqt.h \
    adapterwidget.h \
    mps_coordinate.pb.h \
    mainwindow.h \
    trailercallback.h

SOURCES += \
    myhandler.cpp \
    viewerqt.cpp \
    adapterwidget.cpp \
    mps_coordinate.pb.cc \
    mainwindow.cpp \
    trailercallback.cpp

FORMS += \
    mainwindow.ui
