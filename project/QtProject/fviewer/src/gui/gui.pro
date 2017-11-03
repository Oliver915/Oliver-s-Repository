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

macx {
    INCLUDEPATH += $$PWD/../../../../OpenSceneGraph/include
    LIBS += -L$$PWD/../../../../OpenSceneGraph/lib
    QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.12
}

HEADERS += \
    viewerqt.h \
    adapterwidget.h \
    mps_coordinate.pb.h \
    mainwindow.h \
    trailercallback.h \
    mpstrackballmanipulator.h \
    mpsdatamanager.h \
    mpshudhandler.h \
    mpssideviewmanipulator.h \
    inputdialog.h

SOURCES += \
    viewerqt.cpp \
    adapterwidget.cpp \
    mps_coordinate.pb.cc \
    mainwindow.cpp \
    trailercallback.cpp \
    mpstrackballmanipulator.cpp \
    mpsdatamanager.cpp \
    mpshudhandler.cpp \
    mpssideviewmanipulator.cpp \
    inputdialog.cpp

FORMS += \
    mainwindow.ui

RESOURCES += \
    ../../res/res.qrc
