#include "adapterwidget.h"
#include "viewerqt.h"

int main(int argc, char** argv)
{
    QApplication a(argc, argv);
    osg::ref_ptr<osg::Group> root = new osg::Group();
    osg::ref_ptr<osg::Node> loadedMap = osgDB::readNodeFile(
            "/home/mengyu/material/simpleMap.osg");
    osg::ref_ptr<osg::Node> loadedModel =
            osgDB::readNodeFile(
                    "/home/mengyu/material/"
                    "gliderZoomIn.osg");
    root->addChild(loadedMap.get());
    root->addChild(loadedModel.get());

    ViewerQT* ViewerWindow = new ViewerQT;
    ViewerWindow->setCameraManipulator(
            new osgGA::TrackballManipulator);
    ViewerWindow->getCamera()->setClearColor(
            osg::Vec4(0., 0., 0., 1.));
    ViewerWindow->setSceneData(root.get());

    QMainWindow* mw = new QMainWindow();
    mw->showMaximized();
    mw->setCentralWidget(ViewerWindow);
    mw->show();
    a.connect(
            &a, SIGNAL(lastWindowClosed()), &a,
            SLOT(quit()));

    return a.exec();
    delete mw;
    delete ViewerWindow;
}
