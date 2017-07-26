CONFIG += create_prl staticlib
CONFIG += c++11

QT += core gui opengl

TEMPLATE = lib

TARGET = gui

DESTDIR =$$OUT_PWD/../lib

macx {
    Framework_path = $$PWD/../../3rdparty/Frameworks

    INCLUDEPATH += \
        $$Framework_path/GEOS.framework/Headers \
        $$Framework_path/qgis_core.framework/Headers
}

HEADERS += \
    uav.h \
    createhud_viewpoint.h \
    myhandler.h \
    findnodevisitor.h \
    viewerqt.h \
    adapterwidget.h

SOURCES += \
    uav.cpp \
    createhud_viewpoint.cpp \
    myhandler.cpp \
    findnodevisitor.cpp \
    viewerqt.cpp \
    adapterwidget.cpp

LIBS  +=  -losg -losgDB -losgViewer -losgGA -losgUtil -losgQt -lOpenThreads -losgAnimation -losgText -losgSim
