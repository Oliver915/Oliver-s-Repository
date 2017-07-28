#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    std::string fileName =
            "/home/lzt/AllProjects/TeachersProject/"
            "readroute/fmps_simu_result.dat";

    iReader.open(fileName, std::ios::in | std::ios::binary);
    pIStream = new IstreamInputStream(&iReader);
    pCodeStream = new CodedInputStream(pIStream);

    //
    ui->setupUi(this);
    osg::ref_ptr<osg::Node> loadedMap = osgDB::readNodeFile(
            "/home/lzt/material/SimpleMap.osg");
    //加载UAV
    loadUAV();
    modelRoot = new osg::Group;
    addUAVStoModelRoot(modelRoot);
    //    NumUAV = modelRoot->getNumChildren();
    //加载HUD
    osgText::Text* text = new osgText::Text;
    //构建节点树
    osg::ref_ptr<osg::Group> root = new osg::Group;
    root->addChild(loadedMap.get());
    root->addChild(createHUD_viewPoint(text));
    root->addChild(modelRoot);

    ViewerQT* ViewerWindow = new ViewerQT;
    ViewerWindow->getCamera()->setClearColor(
            osg::Vec4(0.3, 0.3, 0.3, 0.3));
    ViewerWindow->setSceneData(root.get());
    ViewerWindow->setCameraManipulator(
            new MyHandler(modelRoot, text));
    this->showMaximized();
    this->setCentralWidget(ViewerWindow);
    osg::ref_ptr<osg::StateSet> viewerSet =
            new osg::StateSet;
    viewerSet->setMode(
            GL_MULTISAMPLE_ARB, osg::StateAttribute::ON);
    connect(&_timer, SIGNAL(timeout()), this,
            SLOT(changeUAVdof()));
    connect(&_timer, SIGNAL(timeout()), ViewerWindow,
            SLOT(updateGL()));
    _timer.start(2);  //使用start()来开始
}

MainWindow::~MainWindow()
{
    delete ui;
    delete pCodeStream;
    delete pIStream;
    iReader.close();
}
osgSim::DOFTransform* MainWindow::initModel(
        int color, string index)
{
    UAV* glider = new UAV;
    osg::ref_ptr<osg::Node> loadedModel =
            glider->CreateGlider(color, index);
    doft = new osgSim::DOFTransform;
    doft->setCurrentScale(osg::Vec3(1.f, 1.f, 1.f));
    doft->addChild(loadedModel.get());
    doft->setName(index);
    return doft;
    delete glider;
}

void MainWindow::loadUAV()
{
    doft1 = new osgSim::DOFTransform;
    doft2 = new osgSim::DOFTransform;
    doft3 = new osgSim::DOFTransform;
    doft1 = initModel(4, "1");
    doft2 = initModel(1, "2");
    doft3 = initModel(3, "3");
}

void MainWindow::addUAVStoModelRoot(osg::Group* modelRoot)
{
    modelRoot->addChild(doft1);
    modelRoot->addChild(doft2);
    modelRoot->addChild(doft3);
}

void MainWindow::changeUAVdof()
{
    Arena arena;
    uint32_t type;
    // First, read the len of object MpsPlane
    for (int m = 0; m < 3; ++m)
    {
        if (pCodeStream->ReadVarint32(&type))
        {
            uint32_t len;
            if (!pCodeStream->ReadVarint32(&len)) break;

            string codeString;
            if (!pCodeStream->ReadString(&codeString, len))
                break;

            if (type >= 3000000000 && type <= 3999999999)
            {
                MpsSPlane* pPlane =
                        Arena::CreateMessage<MpsSPlane>(
                                &arena);
                pPlane->ParseFromString(codeString);
                temp = dynamic_cast<osgSim::DOFTransform*>(
                        modelRoot->getChild(m));
                changeUAV(pPlane, temp);
            }
        }
    }
}

void MainWindow::changeUAV(
        MpsSPlane* pPlane, osgSim::DOFTransform* temp)
{
    unsigned int trans = 180 / 3.14159;
    if (pPlane == nullptr) return;
    //    const MpsSHeader& head = pPlane->head();
    const MpsSPosition& pos = pPlane->pos();
    temp->setCurrentTranslate(
            osg::Vec3(pos.lng(), pos.lat(), pos.h() / 10));
    temp->setCurrentHPR(osg::Vec3(
            pPlane->yaw() / trans, pPlane->pitch() / trans,
            pPlane->roll() / trans));
}
