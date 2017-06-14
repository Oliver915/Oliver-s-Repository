#include "adapterwidget.h"
#include "viewerqt.h"

int main(int argc, char** argv)
{
    QApplication a(argc, argv);
    osg::ref_ptr<osg::Node> loadedModel =
            osgDB::readNodeFile(
                    "/usr/share/openscenegraph/data/"
                    "cow.osg");
    ViewerQT* ViewerWindow = new ViewerQT;
    ViewerWindow->setCameraManipulator(
            new osgGA::TrackballManipulator);
    ViewerWindow->setSceneData(loadedModel.get());

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
