#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , modelRoot(nullptr)
    , pIStream(nullptr)
    , pCodeStream(nullptr)
    , viewerWindow(nullptr)
{
    //启动ui
    ui->setupUi(this);

    //为读取文件做准备
    std::string fileName =
            "../material/fmps_simu_result.dat";
    iReader.open(fileName, std::ios::in | std::ios::binary);
    // TODO : 处理iReader打开文件失败的情况
    pIStream = new IstreamInputStream(&iReader);
    pCodeStream = new CodedInputStream(pIStream);

    //加载地图
    osg::ref_ptr<osg::Group> root = new osg::Group;
    osg::ref_ptr<osg::Node> loadedMap = osgDB::readNodeFile(
            "../material/SimpleMap.osg");
    root->addChild(loadedMap.get());

    // 加载HUD
    osgText::Text* text = new osgText::Text;
    root->addChild(createHUD_viewPoint(text));

    // 加载UAV
    osg::Node* model1 =
            osgDB::readNodeFile("../material/rq1b.osg");
    osg::Node* model2 =
            osgDB::readNodeFile("../material/rq1b.osg");
    osg::Node* model3 =
            osgDB::readNodeFile("../material/rq1b.osg");
    modelRoot = new osg::Group;
    // TODO : 修复假定飞机数量和已知ID的假定
    osg::ref_ptr<osgSim::DOFTransform> doft1 =
            CreateUAV("1", 1, model1);
    osg::ref_ptr<osgSim::DOFTransform> doft2 =
            CreateUAV("2", 2, model2);
    osg::ref_ptr<osgSim::DOFTransform> doft3 =
            CreateUAV("3", 3, model3);
    id_uav_map.insert(1034553527, doft1);
    id_uav_map.insert(3474710540, doft2);
    id_uav_map.insert(4218261403, doft3);

    modelRoot->addChild(doft1);
    modelRoot->addChild(doft2);
    modelRoot->addChild(doft3);
    root->addChild(modelRoot);

    //加载飞机轨迹线
    osg::Geometry* geometryTrack1 =
            createRibbon(osg::Vec3(1.0f, 0.0f, 1.0f));
    osg::ref_ptr<osg::Geode> geodeTrack1 = new osg::Geode;
    geodeTrack1->addDrawable(geometryTrack1);
    geodeTrack1->getOrCreateStateSet()->setMode(
            GL_LIGHTING, osg::StateAttribute::OFF);
    geodeTrack1->getOrCreateStateSet()->setMode(
            GL_BLEND, osg::StateAttribute::ON);
    geometryTrack1->getOrCreateStateSet()->setRenderingHint(
            osg::StateSet::TRANSPARENT_BIN);
    root->addChild(geodeTrack1);

    //无人机与轨迹线匹配
    doft2->addUpdateCallback(
            new TrailerCallback(geometryTrack1));

    // 对ViewerWindow进行初始化
    viewerWindow = new ViewerQT;
    viewerWindow->getCamera()->setClearColor(
            osg::Vec4(0.f, 0.6, 0.7, 0.25));
    viewerWindow->setSceneData(root.get());
    setCentralWidget(viewerWindow);

    //对viewerWindow漫游器的设置。
    // 1.MyHandler
    osg::ref_ptr<MyHandler> myHandler =
            new MyHandler(text, &id_uav_map);
    //    viewerWindow->setCameraManipulator(myHandler.get());

    // 2.nodeTrackerManipulator
    double x = doft3->getCurrentTranslate().x();
    double y = doft3->getCurrentTranslate().y();
    double z = doft3->getCurrentTranslate().z();
    osg::ref_ptr<osgGA::NodeTrackerManipulator>
            nodeTracker = new osgGA::NodeTrackerManipulator;
        nodeTracker->setHomePosition(
                osg::Vec3(x-1000 , y , z + 300),
                doft1->getCurrentTranslate(), osg::Vec3(0.0, 0.0, 1.0));
    nodeTracker->setTrackerMode(
            osgGA::NodeTrackerManipulator::
                    NODE_CENTER_AND_ROTATION);
    nodeTracker->setRotationMode(
            osgGA::NodeTrackerManipulator::TRACKBALL);
    nodeTracker->setTrackNode(model3);

    //设置键盘操作转换漫游器
    osg::ref_ptr<osgGA::KeySwitchMatrixManipulator>
            keySwitch =
                    new osgGA::KeySwitchMatrixManipulator;
    keySwitch->addMatrixManipulator(
            'm', "MyHandler", myHandler.get());
    keySwitch->addMatrixManipulator(
            'n', "NodeTracker", nodeTracker.get());
    viewerWindow->setCameraManipulator(keySwitch.get());

    //    viewerWindow->addEventHandler(new
    //    FollowUpdater(doft2));

    //每200ms进行changeUAVdof()操作
    connect(&updateTimer, SIGNAL(timeout()), this,
            SLOT(changeUAVdof()));
    updateTimer.start(10);

    // 界面最大化
    showMaximized();
}

MainWindow::~MainWindow()
{
    delete ui;
    delete pCodeStream;
    delete pIStream;
    iReader.close();
}

osg::ref_ptr<osgSim::DOFTransform> MainWindow::CreateUAV(
        std::string index, int color, osg::Node* UAV)
{
    //加载无人机模型
    //    osg::ref_ptr<osg::Node> UAV = new osg::Node;
    //    UAV = osgDB::readNodeFile("../material/rq1b.osg");

    //加载无人机纹理图片
    osg::ref_ptr<osg::Image> skin = new osg::Image;
    switch (color)
    {
        case 0:
            skin = osgDB::readImageFile(
                    "../material/red.png");
            break;
        case 1:
            skin = osgDB::readImageFile(
                    "../material/blue.png");
            break;
        case 2:
            skin = osgDB::readImageFile(
                    "../material/green.png");
            break;
        case 3:
            skin = osgDB::readImageFile(
                    "../material/yellow.png");
            break;
        default:
            skin = osgDB::readImageFile(
                    "../material/pink.png");
            break;
    }

    //给无人机模型加纹理
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
    UAV->setStateSet(state.get());

    // 创建无人机编号，并设置其位置在无人机模型正上方
    osg::ref_ptr<osg::Geode> textGeode = new osg::Geode;
    osg::ref_ptr<osgText::Font> font =
            osgText::readFontFile("../material/arial.ttf");
    osg::ref_ptr<osgText::Text> text = new osgText::Text;
    text->setFont(font.get());
    text->setText(index);
    text->setPosition(osg::Vec3(0.f, 0.f, 5.f));
    text->setAxisAlignment(osgText::Text::SCREEN);
    text->setAlignment(osgText::Text::CENTER_BOTTOM);
    text->setCharacterSize(40.f);
    textGeode->addDrawable(text.get());

    // 将加过纹理的无人机模型和编号加载到组节点上，并且设置组节点的
    // HPR角的范围
    osg::ref_ptr<osgSim::DOFTransform> grp =
            new osgSim::DOFTransform;
    grp->addChild(UAV);
    grp->addChild(textGeode.get());
    grp->setCurrentScale(osg::Vec3(20.f, 20.f, 20.f));
    grp->setMaxHPR(osg::Vec3(
            3.14159 * 2, 3.14159 / 4.0, 3.14159 / 4.0));
    grp->setMinHPR(osg::Vec3(
            -3.14159 * 2, 3.14159 / 4.0, 3.14159 / 4.0));
    grp->setName(index);
    return grp;
}

osg::Geometry* MainWindow::createRibbon(
        const osg::Vec3& colorRGB)
{
    //顶点数组、法线数组、颜色数组的定义
    osg::ref_ptr<osg::Vec3Array> vertices =
            new osg::Vec3Array(g_numPoints);
    osg::ref_ptr<osg::Vec3Array> normals =
            new osg::Vec3Array(g_numPoints);
    osg::ref_ptr<osg::Vec4Array> colors =
            new osg::Vec4Array(g_numPoints);

    //三个数组的初始化
    osg::Vec3 origin = osg::Vec3(-31147.7, -25028.0, 60.4);
    osg::Vec3 normal = osg::Vec3(-31147.7, -25028.0, 60.4);
    for (unsigned int i = 0; i < g_numPoints - 1; i += 2)
    {
        (*vertices)[i] = origin;
        (*vertices)[i + 1] = origin;
        (*normals)[i] = normal;
        (*normals)[i + 1] = normal;

        double alpha =
                /*(double)i / (double)g_numPoints*/ 0.5;
        (*colors)[i] = osg::Vec4(colorRGB, alpha);
        (*colors)[i + 1] = osg::Vec4(colorRGB, alpha);
    }

    //轨迹带的状态设置
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
            GL_QUAD_STRIP, 0, g_numPoints));
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

    //读取文件，并进行changeUAV的操作
    if (type >= 3000000000 && type <= 3999999999)
    {
        MpsSPlane* pPlane =
                Arena::CreateMessage<MpsSPlane>(&arena);
        pPlane->ParseFromString(codeString);

        osgSim::DOFTransform* pUAV =
                id_uav_map.value(pPlane->head().id());
        if (pUAV == nullptr) return;

        changeUAV(pPlane, pUAV);
    }

    // update osg viewer
    viewerWindow->updateGL();
}

void MainWindow::changeUAV(
        MpsSPlane* pPlane, osgSim::DOFTransform* pUAV)
{
    //从地球经纬度到二维x,y坐标的转化
    const double TRANS = 180 / 3.14159;
    const double PI = 3.1415926;
    const double mass = 20037508.34;
    if (pPlane == nullptr) return;

    const MpsSPosition& pos = pPlane->pos();
    double x = ((pos.lng() * mass) / 180 - 4950000);
    double y = log(tan((90 + pos.lat()) * PI / 360)) /
               (PI / 180);
    y = (y * mass / 180 - 1450000);

    //改变无人机自由度
    pUAV->setCurrentTranslate(osg::Vec3(x, y, pos.h()));
    pUAV->setCurrentHPR(osg::Vec3(
            pPlane->yaw() / (-TRANS),
            pPlane->pitch() / TRANS,
            pPlane->roll() / TRANS));
}

osg::Node* MainWindow::createHUD_viewPoint(
        osgText::Text* text)
{
    //对HUD相机的text进行初始化
    osg::ref_ptr<osgText::Font> font =
            osgText::readFontFile("../material/arial.ttf");
    text->setFont(font);
    osg::Vec3 position(10.0f, 880.0f, 0.0f);
    text->setPosition(position);
    text->setColor(osg::Vec4(1.f, 1.f, 0.f, 1.f));
    text->setText(L"");
    text->setCharacterSize(15.f);
    text->setDataVariance(osg::Object::DYNAMIC);

    //对HUD相机的子节点geode进行初始化
    osg::Geode* geode = new osg::Geode;
    geode->addDrawable(text);
    osg::StateSet* stateset = geode->getOrCreateStateSet();
    stateset->setMode(
            GL_LIGHTING, osg::StateAttribute::OFF);
    stateset->setMode(
            GL_DEPTH_TEST, osg::StateAttribute::OFF);
    stateset->setMode(GL_BLEND, osg::StateAttribute::ON);

    //对HUD相机进行初始化
    osg::Camera* camera = new osg::Camera;
    camera->setProjectionMatrix(
            osg::Matrix::ortho2D(0, 1600, 0, 900));
    camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
    camera->setViewMatrix(osg::Matrix::identity());
    camera->setClearMask(GL_DEPTH_BUFFER_BIT);
    camera->setAllowEventFocus(false);
    camera->setRenderOrder(osg::Camera::POST_RENDER);
    camera->addChild(geode);

    return camera;
}
