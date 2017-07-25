#include <osgGA/TrackballManipulator>
#include <osgViewer/ViewerEventHandlers>
#include "adapterwidget.h"
#include "chud_viewpoint.h"
#include "createhud_viewpoint.h"
#include "myhandler.h"
#include "pickhandler.h"
#include "uav.h"
#include "viewerqt.h"

int main(int argc, char** argv)
{
    QApplication a(argc, argv);
    osg::ref_ptr<osg::Group> root = new osg::Group();
    osg::ref_ptr<osg::Node> loadedMap = osgDB::readNodeFile(
            "/home/lzt/material/SimpleMap.osg");

    UAV* glider1 = new UAV;
    UAV* glider2 = new UAV;
    UAV* glider3 = new UAV;
    UAV* glider4 = new UAV;
    UAV* glider5 = new UAV;
    osg::ref_ptr<osg::Node> loadedModel1 =
            glider1->CreateGlider(4, "1");
    osg::ref_ptr<osg::Node> loadedModel2 =
            glider2->CreateGlider(1, "2");
    osg::ref_ptr<osg::Node> loadedModel3 =
            glider3->CreateGlider(3, "3");
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
    osg::ref_ptr<osgSim::DOFTransform> pickDof =
            new osgSim::DOFTransform;
    osg::ref_ptr<osgSim::DOFTransform> doft1 =
            new osgSim::DOFTransform;
    osg::ref_ptr<osgSim::DOFTransform> doft2 =
            new osgSim::DOFTransform;
    osg::ref_ptr<osgSim::DOFTransform> doft3 =
            new osgSim::DOFTransform;
    pickDof->setCurrentScale(osg::Vec3(1.f, 1.f, 1.f));
    doft1->setCurrentScale(osg::Vec3(1.f, 1.f, 1.f));
    doft2->setCurrentScale(osg::Vec3(1.f, 1.f, 1.f));
    doft3->setCurrentScale(osg::Vec3(1.f, 1.f, 1.f));
    doft1->addChild(loadedModel1.get());
    doft2->addChild(loadedModel2.get());
    doft3->addChild(loadedModel3.get());
    doft1->setName("1");
    doft2->setName("2");
    doft3->setName("3");
    osg::ref_ptr<osg::Group> ModelRoot = new osg::Group;

    ModelRoot->addChild(doft1);
    ModelRoot->addChild(doft2);
    ModelRoot->addChild(doft3);
    root->addChild(loadedMap.get());
    root->addChild(ModelRoot.get());
    //    osg::ref_ptr<MyHandler> ctrler =
    //            new MyHandler(doft.get());

    //    root->addChild(loadedModel3);
    //    root->addChild(loadedModel4);
    //    root->addChild(loadedModel5);
    osgText::Text* text = new osgText::Text;
    osg::ref_ptr<CHUD_viewPoint> pHUD =
            new CHUD_viewPoint(text, pickDof.get());
    root->addChild(createHUD_viewPoint(text));

    ViewerQT* ViewerWindow = new ViewerQT;
    ViewerWindow->getCamera()->setClearColor(
            osg::Vec4(0.3, 0.3, 0.3, 0.3));
    ViewerWindow->setSceneData(root.get());
    ViewerWindow->setCameraManipulator(
            new MyHandler(ModelRoot.get(),text));
//    ViewerWindow->addEventHandler(
//            new PickHandler(pickDof.get()));
    ViewerWindow->addEventHandler(pHUD.get());
    QMainWindow* mw = new QMainWindow();
    mw->showMaximized();
    mw->setCentralWidget(ViewerWindow);
    osg::ref_ptr<osg::StateSet> ViewerSet =
            new osg::StateSet;
    ViewerSet->setMode(
            GL_MULTISAMPLE_ARB, osg::StateAttribute::ON);
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
