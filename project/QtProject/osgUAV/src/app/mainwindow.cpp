#include "mainwindow.h"
#include <osgGA/TrackballManipulator>
#include <osgViewer/ViewerEventHandlers>
#include "createhud_viewpoint.h"
#include "myhandler.h"
#include "uav.h"
#include "ui_mainwindow.h"
#include "viewerqt.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    osg::ref_ptr<osg::Group> root = new osg::Group();
    osg::ref_ptr<osg::Node> loadedMap = osgDB::readNodeFile(
            "/home/lzt/material/SimpleMap.osg");

    UAV* glider1 = new UAV;
    UAV* glider2 = new UAV;
    UAV* glider3 = new UAV;

    osg::ref_ptr<osg::Node> loadedModel1 =
            glider1->CreateGlider(4, "1");
    osg::ref_ptr<osg::Node> loadedModel2 =
            glider2->CreateGlider(1, "2");
    osg::ref_ptr<osg::Node> loadedModel3 =
            glider3->CreateGlider(3, "3");

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
    osgText::Text* text = new osgText::Text;

    root->addChild(createHUD_viewPoint(text));

    ViewerQT* ViewerWindow = new ViewerQT;
    ViewerWindow->getCamera()->setClearColor(
            osg::Vec4(0.3, 0.3, 0.3, 0.3));
    ViewerWindow->setSceneData(root.get());
    ViewerWindow->setCameraManipulator(
            new MyHandler(ModelRoot.get(), text));
    this->showMaximized();
    this->setCentralWidget(ViewerWindow);
    osg::ref_ptr<osg::StateSet> viewerSet =
            new osg::StateSet;
    viewerSet->setMode(
            GL_MULTISAMPLE_ARB, osg::StateAttribute::ON);
}

MainWindow::~MainWindow() { delete ui; }
