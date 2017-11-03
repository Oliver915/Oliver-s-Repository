#include "mainwindow.h"
#include <osg/TexGen>
#include <osgGA/KeySwitchMatrixManipulator>
#include "mpsdatamanager.h"
#include "trailercallback.h"
#include "ui_mainwindow.h"

static const double PI = 3.1415926;
static const double CONVERT_FACTOR = 20037508.34;
static const double TRANS = 180 / PI;

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , modelRoot(nullptr)
    , pIStream(nullptr)
    , pCodeStream(nullptr)
    , viewerWindow(nullptr)
    , pHUDHandler(nullptr)
{
    // setup ui
    ui->setupUi(this);

    // get ready for read data
    std::string fileName =
            "../fviewer/res/data/"
            "fmps_simu_result.dat";
    iReader.open(fileName, std::ios::in | std::ios::binary);
    pIStream = new IstreamInputStream(&iReader);
    pCodeStream = new CodedInputStream(pIStream);

    // load map
    root = new osg::Group;
    osg::ref_ptr<osg::Node> loadedMap = osgDB::readNodeFile(
            "../fviewer/res/osgModels/"
            "SimpleMap.osg");
    root->addChild(loadedMap.get());

    // load HUD
    osgText::Text* text = new osgText::Text;
    root->addChild(createHUD_viewPoint(text));

    // UAV modelRoot
    modelRoot = new osg::Group;
    root->addChild(modelRoot);

    // init ViewerWindow
    viewerWindow = new ViewerQT;
    viewerWindow->getCamera()->setClearColor(
            osg::Vec4(0.f, 0.6, 0.7, 0.25));
    viewerWindow->setSceneData(root);
    setCentralWidget(viewerWindow);

    createMenuBar();
    createToolBar();

    // Setup HUB handler
    pHUDHandler = new MpsHUDHandler(text);

    // two kinds of manipulators
    // 1.MyHandler
    pTrackballManipulator =
            new MpsTrackballManipulator(pHUDHandler);

    // 2.sideOrBehindViewManipulator
    pSideView = new MpsSideViewManipulator(pHUDHandler);
    pSideView->setTrackerMode(
            osgGA::NodeTrackerManipulator::
                    NODE_CENTER_AND_ROTATION);
    pSideView->setRotationMode(
            osgGA::NodeTrackerManipulator::TRACKBALL);

    // switch the manipulators by keyboard
    osg::ref_ptr<osgGA::KeySwitchMatrixManipulator>
            keySwitch =
                    new osgGA::KeySwitchMatrixManipulator;
    keySwitch->addMatrixManipulator(
            'm', "MpsTrackballManipulator",
            pTrackballManipulator);
    keySwitch->addMatrixManipulator(
            'n', "NodeTracker", pSideView);
    viewerWindow->setCameraManipulator(keySwitch.get());

    // use the function changeUAVdof() per 10ms
    connect(&updateTimer, SIGNAL(timeout()), this,
            SLOT(changeUAVdof()));
    updateTimer.start(10);

    // click the manu UAV;
    connect(searchUAV, SIGNAL(triggered()), this,
            SLOT(clickUAV()));

    // click the tool show/hide;
    connect(showAction, SIGNAL(triggered()), this,
            SLOT(clickShow()));
    connect(hideAction, SIGNAL(triggered()), this,
            SLOT(clickHide()));

    // click the tool ZoomIn/ZoomOut;
    connect(ui->actionZoomIn, SIGNAL(triggered(bool)), this,
            SLOT(clickZoomIn()));
    connect(ui->actionZoomOut, SIGNAL(triggered(bool)),
            this, SLOT(clickZoomOut()));

    // click the tool Side/Behind
    connect(ui->actionSide, SIGNAL(triggered(bool)), this,
            SLOT(clickSideView()));

    // maximize ui
    showMaximized();
}

MainWindow::~MainWindow()
{
    delete pCodeStream;
    delete pIStream;
    iReader.close();

    delete pHUDHandler;
    delete ui;
}

osgSim::DOFTransform* MainWindow::createUAV(
        std::string index, int color)
{
    // load UAV models
    osg::ref_ptr<osg::Node> pUAV = osgDB::readNodeFile(
            "../fviewer/res/osgModels/rq1b.osg");

    // load UAV skin image
    osg::ref_ptr<osg::Image> skin;
    switch (color)
    {
        case 0:
            skin = osgDB::readImageFile(
                    "../fviewer/res/colors/"
                    "red.png");
            break;
        case 1:
            skin = osgDB::readImageFile(
                    "../fviewer/res/colors/"
                    "green.png");
            break;
        case 2:
            skin = osgDB::readImageFile(
                    "../fviewer/res/colors/"
                    "yellow.png");
            break;
        default:
            skin = osgDB::readImageFile(
                    "../fviewer/res/colors/"
                    "pink.png");
            break;
    }

    // add texture to UAVs
    osg::ref_ptr<osg::Texture2D> texture =
            new osg::Texture2D;
    texture->setImage(skin.get());

    osg::ref_ptr<osg::TexGen> texgen = new osg::TexGen();
    texgen->setMode(osg::TexGen::SPHERE_MAP);

    osg::ref_ptr<osg::TexEnv> texenv = new osg::TexEnv();
    texenv->setMode(osg::TexEnv::Mode::ADD);

    osg::ref_ptr<osg::StateSet> state = new osg::StateSet;
    state->setTextureAttributeAndModes(
            1, texture.get(), osg::StateAttribute::ON);
    state->setTextureAttributeAndModes(
            1, texgen.get(), osg::StateAttribute::ON);
    state->setTextureAttributeAndModes(1, texenv.get());
    pUAV->setStateSet(state.get());

    // create the index of UAV,and set it above the UAV
    // model
    osg::ref_ptr<osg::Geode> textGeode = new osg::Geode;
    osg::ref_ptr<osgText::Font> font =
            osgText::readFontFile(
                    "../fviewer/res/fonts/"
                    "arial.ttf");
    osg::ref_ptr<osgText::Text> text = new osgText::Text;
    text->setFont(font.get());
    text->setText(index);
    text->setPosition(osg::Vec3(0.f, 0.f, 10.f));
    text->setAxisAlignment(osgText::Text::SCREEN);
    text->setAlignment(osgText::Text::CENTER_BOTTOM);
    text->setCharacterSize(40.f);
    textGeode->addDrawable(text.get());

    // add the UAV model which has loaded the texture to the
    // group node,define the group node's range of the HPR.
    osgSim::DOFTransform* grp = new osgSim::DOFTransform;
    grp->addChild(pUAV);
    grp->setChild(0, pUAV);
    grp->addChild(textGeode.get());
    grp->setCurrentScale(osg::Vec3(20.f, 20.f, 20.f));
    grp->setMaxHPR(osg::Vec3(PI * 2, PI / 4.0, PI / 4.0));
    grp->setMinHPR(osg::Vec3(-PI * 2, PI / 4.0, PI / 4.0));
    grp->setName(index);
    return grp;
}

osg::Geometry* MainWindow::createRibbon(
        const osg::Vec3& colorRGB)
{
    // define the vertices array,normal array,color array
    osg::ref_ptr<osg::Vec3Array> vertices =
            new osg::Vec3Array(G_NUM_POINTS);
    osg::ref_ptr<osg::Vec3Array> normals =
            new osg::Vec3Array(G_NUM_POINTS);
    osg::ref_ptr<osg::Vec4Array> colors =
            new osg::Vec4Array(G_NUM_POINTS);

    // init three arrays
    osg::Vec3 origin = osg::Vec3(-31147.7, -25028.0, 60.4);
    osg::Vec3 normal = osg::Vec3(-31147.7, -25028.0, 60.4);
    for (unsigned int i = 0; i < G_NUM_POINTS - 1; i += 2)
    {
        (*vertices)[i] = origin;
        (*vertices)[i + 1] = origin;
        (*normals)[i] = normal;
        (*normals)[i + 1] = normal;

        double alpha = (double)i / (double)G_NUM_POINTS;
        (*colors)[i] = osg::Vec4(colorRGB, alpha);
        (*colors)[i + 1] = osg::Vec4(colorRGB, alpha);
    }

    // set the state of track ribbon
    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
    geom->setDataVariance(osg::Object::DYNAMIC);
    geom->setUseDisplayList(false);
    geom->setUseVertexBufferObjects(true);
    geom->setVertexArray(vertices.get());
    geom->setNormalArray(normals.get());
    geom->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);
    geom->setColorArray(colors.get());
    geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
    geom->addPrimitiveSet(new osg::DrawArrays(
            GL_QUAD_STRIP, 0, G_NUM_POINTS));
    return geom.release();
}

void MainWindow::changeUAVdof()
{
    Arena arena;

    uint32_t type = 0;
    if (!pCodeStream->ReadVarint32(&type)) return;

    uint32_t len = 0;
    if (!pCodeStream->ReadVarint32(&len)) return;

    std::string codeString;
    if (!pCodeStream->ReadString(&codeString, len)) return;

    // read the file,and changeUAV
    if (type >= 3000000000 && type <= 3999999999)
    {
        MpsSPlane* pPlane =
                Arena::CreateMessage<MpsSPlane>(&arena);
        pPlane->ParseFromString(codeString);

        uint32_t id = pPlane->head().id();

        osgSim::DOFTransform* pUAV =
                MpsDataManager::instance()->findUAV(id);
        if (pUAV == nullptr)
        {
            int curSize =
                    MpsDataManager::instance()->mapSize();
            int intIndex = curSize + 1;
            std::string strIndex = std::to_string(intIndex);

            // create the UAV node
            osgSim::DOFTransform* pUAVnewCreated =
                    createUAV(strIndex, curSize % 4);
            MpsDataManager::instance()->addUAV(
                    id, intIndex, pUAVnewCreated);

            modelRoot->addChild(pUAVnewCreated);

            // change the flight state of UAV
            changeUAV(pPlane, pUAVnewCreated);

            // create the flight trackline of the
            // UAV
            osg::Geometry* geometryTrack = createRibbon(
                    osg::Vec3(1.0f, 0.0f, 1.0f));
            osg::ref_ptr<osg::Geode> geodeTrack =
                    new osg::Geode;
            addGeometryToGeode(geometryTrack, geodeTrack);
            root->addChild(geodeTrack);

            // match the trackline to UAV
            pUAVnewCreated->addUpdateCallback(
                    new TrailerCallback(geometryTrack));
        }
        else
        {
            changeUAV(pPlane, pUAV);
        }
    }

    // update osg viewer
    viewerWindow->updateGL();
}

osg::Vec3 MainWindow::transformLatAndLonToXYZ(
        MpsSPlane* pPlane)
{
    Q_ASSERT(pPlane != nullptr);

    const MpsSPosition& pos = pPlane->pos();
    double x =
            ((pos.lng() * CONVERT_FACTOR) / 180 - 4950000);
    double y = log(tan((90 + pos.lat()) * PI / 360)) /
               (PI / 180);
    y = (y * CONVERT_FACTOR / 180 - 1450000);

    return osg::Vec3(x, y, pos.h());
}

void MainWindow::changeUAV(
        MpsSPlane* pPlane, osgSim::DOFTransform* pUAV)
{
    if (pPlane == nullptr || pUAV == nullptr) return;

    // change the dof of UAV
    pUAV->setCurrentTranslate(
            transformLatAndLonToXYZ(pPlane));
    pUAV->setCurrentHPR(osg::Vec3(
            pPlane->yaw() / (-TRANS),
            pPlane->pitch() / TRANS,
            pPlane->roll() / TRANS));
}

osg::Node* MainWindow::createHUD_viewPoint(
        osgText::Text* text)
{
    Q_ASSERT(text != nullptr);

    // init the text of HUD camera
    osg::ref_ptr<osgText::Font> font =
            osgText::readFontFile(
                    "../fviewer/res/fonts/"
                    "arial.ttf");
    text->setFont(font);
    osg::Vec3 position(10.0f, 880.0f, 0.0f);
    text->setPosition(position);
    text->setColor(osg::Vec4(1.f, 1.f, 0.f, 1.f));
    text->setText(L"");
    text->setCharacterSize(15.f);
    text->setDataVariance(osg::Object::DYNAMIC);

    // init the geode which is the child node of HUD camera
    textGeode = new osg::Geode;
    textGeode->addDrawable(text);
    osg::StateSet* stateset =
            textGeode->getOrCreateStateSet();
    stateset->setMode(
            GL_LIGHTING, osg::StateAttribute::OFF);
    stateset->setMode(
            GL_DEPTH_TEST, osg::StateAttribute::OFF);
    stateset->setMode(GL_BLEND, osg::StateAttribute::ON);

    // init the HUD camara
    osg::Camera* camera = new osg::Camera;
    camera->setProjectionMatrix(
            osg::Matrix::ortho2D(0, 1600, 0, 900));
    camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
    camera->setViewMatrix(osg::Matrix::identity());
    camera->setClearMask(GL_DEPTH_BUFFER_BIT);
    camera->setAllowEventFocus(false);
    camera->setRenderOrder(osg::Camera::POST_RENDER);
    camera->addChild(textGeode);

    return camera;
}

void MainWindow::addGeometryToGeode(
        osg::Geometry* geometryTrack,
        osg::Geode* geodeTrack)
{
    Q_ASSERT(geometryTrack != nullptr);
    Q_ASSERT(geodeTrack != nullptr);

    geodeTrack->addDrawable(geometryTrack);
    geodeTrack->getOrCreateStateSet()->setMode(
            GL_LIGHTING, osg::StateAttribute::OFF);
    geodeTrack->getOrCreateStateSet()->setMode(
            GL_BLEND, osg::StateAttribute::ON);
    geometryTrack->getOrCreateStateSet()->setRenderingHint(
            osg::StateSet::TRANSPARENT_BIN);
}

void MainWindow::createMenuBar()
{
    // add manuBar
    searchUAV = new QAction(tr("UAV"), this);
    menu[0] = new QMenu("Search");
    menu[0]->addAction(searchUAV);

    menuBar = new QMenuBar(this);
    menuBar->addMenu(menu[0]);
    menuBar->setGeometry(0, 0, this->width(), 30);
}

void MainWindow::createToolBar()
{
    // add toolBar
    showAction = new QAction(tr("Show"), this);
    hideAction = new QAction(tr("hide"), this);

    fileToolBar = new QToolBar;
    fileToolBar = addToolBar(tr("File"));
    fileToolBar->addAction(showAction);
    fileToolBar->addAction(hideAction);
}

void MainWindow::clickUAV()
{
    inputDlg = new InputDialog(1, this);
    inputDlg->exec();
    pSideView->changeUAVthroughBar(inputDlg->outputIndex());
    pTrackballManipulator->changeUAVthroughBar(
            inputDlg->outputIndex());
}

void MainWindow::clickShow() { textGeode->setNodeMask(1); }
void MainWindow::clickHide()
{
    textGeode->setNodeMask(0X0);
}

void MainWindow::clickZoomIn()
{
    pSideView->clickZoom(-0.2, false);
}

void MainWindow::clickZoomOut()
{
    pSideView->clickZoom(0.2, false);
}

void MainWindow::clickSideView()
{
    pSideView->clickSideView();
}
