#include <osgGA/TrackballManipulator>
#include "adapterwidget.h"
#include "myhandler.h"
#include "uav.h"
#include "viewerqt.h"
//#include <osgViewer/ViewerEventHandlers>
//#include "pickhandler.h"

int main(int argc, char** argv)
{
    QApplication a(argc, argv);
    osg::ref_ptr<osg::Group> root = new osg::Group();
    osg::ref_ptr<osg::Node> loadedMap = osgDB::readNodeFile(
            "/home/mengyu/material/SimpleMap.osg");

    UAV* glider1 = new UAV;
    UAV* glider2 = new UAV;
    UAV* glider3 = new UAV;
    UAV* glider4 = new UAV;
    UAV* glider5 = new UAV;
    osg::ref_ptr<osg::Node> loadedModel1 =
            glider1->CreateGlider(
                    /*10.f, 10.f, 30.f, 60.f, -40.f, 60.f,*/
                    1);
    //    osg::ref_ptr<osg::Node> loadedModel2 =
    //            glider2->CreateGlider(
    //                    //                    -80.f,
    //                    -40.f,
    //                    //                    30.f, 10.f,
    //                    90.f,
    //                    //                    100.f,
    //                    3);
    //    osg::ref_ptr<osg::Node> loadedModel3 =
    //            glider3->CreateGlider(
    //                    //                    80.f, 70.f,
    //                    100.f,
    //                    //                    -80.f,
    //                    -20.f,
    //                    //                    15.f,
    //                    0);
    //    osg::ref_ptr<osg::Node> loadedModel4 =
    //            glider4->CreateGlider(
    //                    //                    60.f, 70.f,
    //                    20.f,
    //                    //                    -90.f,
    //                    -45.f,
    //                    //                    100.f,
    //                    2);
    //    osg::ref_ptr<osg::Node> loadedModel5 =
    //            glider5->CreateGlider(
    //                    /*80.f, 40.f, 80.f, 10.f, 85.f,
    //                    20.f,*/
    //                    4);
    osg::ref_ptr<osg::MatrixTransform> mt =
            new osg::MatrixTransform;
    osg::ref_ptr<osg::Group> Model1Root = new osg::Group;
    mt->addChild(loadedModel1.get());
    Model1Root->addChild(mt);
    root->addChild(loadedMap.get());
    root->addChild(Model1Root.get());
    osg::ref_ptr<MyHandler> ctrler =
            new MyHandler(mt.get());

    //    root->addChild(loadedModel2);
    //    root->addChild(loadedModel3);
    //    root->addChild(loadedModel4);
    //    root->addChild(loadedModel5);

    ViewerQT* ViewerWindow = new ViewerQT;
    ViewerWindow->getCamera()->setClearColor(
            osg::Vec4(0., 0., 0, 0.));
    ViewerWindow->setSceneData(root.get());
    ViewerWindow->setCameraManipulator(
            new MyHandler(mt.get()));
//    osg::ref_ptr<PickHandler> picker =new PickHandler;
//    root->addChild(picker->getOrCreateSelectionBox());
    ViewerWindow->addEventHandler(ctrler.get());
//    ViewerWindow->addEventHandler(new osgViewer::StatsHandler);

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
    delete glider3;
    delete glider4;
    delete glider5;
}
