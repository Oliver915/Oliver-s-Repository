#include "adapterwidget.h"
#include "transform.h"
#include "viewerqt.h"

int main(int argc, char** argv)
{
    QApplication a(argc, argv);
    osg::ref_ptr<osg::Group> root = new osg::Group();
    osg::ref_ptr<osg::Node> loadedMap = osgDB::readNodeFile(
            "/home/mengyu/material/SimpleMap.osg");

    Transform* glider1 = new Transform;
    Transform* glider2 = new Transform;
    Transform* glider3 = new Transform;
    Transform* glider4 = new Transform;
    Transform* glider5 = new Transform;
    osg::ref_ptr<osg::Node> loadedModel1 =
            glider1->CreateGlider(
                    0.f, 0.f, 30.f, 60.f, -40.f, 60.f, 1);
    osg::ref_ptr<osg::Node> loadedModel2 =
            glider2->CreateGlider(
                    -80.f, -40.f, 30.f, 10.f, 90.f, 100.f,
                    3);
    osg::ref_ptr<osg::Node> loadedModel3 =
            glider3->CreateGlider(
                    80.f, 70.f, 100.f, -80.f, -20.f, 15.f,
                    0);
    osg::ref_ptr<osg::Node> loadedModel4 =
            glider4->CreateGlider(
                    60.f, 70.f, 20.f, -90.f, -45.f, 100.f,
                    2);
    osg::ref_ptr<osg::Node> loadedModel5 =
            glider5->CreateGlider(
                    80.f, 40.f, 80.f, 10.f, 85.f, 20.f, 4);
    root->addChild(loadedMap.get());
    root->addChild(loadedModel1);
    root->addChild(loadedModel2);
    root->addChild(loadedModel3);
    root->addChild(loadedModel4);
    root->addChild(loadedModel5);

    ViewerQT* ViewerWindow = new ViewerQT;
    ViewerWindow->setCameraManipulator(
            new osgGA::TrackballManipulator);
    ViewerWindow->getCamera()->setClearColor(
            osg::Vec4(0., 0., 0, 0.));
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
    delete glider1;
    delete glider2;
}
