#include "viewerqt.h"

ViewerQT::ViewerQT(
        QWidget* parent, const char* name,
        const QGLWidget* shareWidget, WindowFlags f)
    : AdapterWidget(parent, name, shareWidget, f)
{
    getCamera()->setViewport(
            new osg::Viewport(0, 0, width(), height()));
    //创建一个对称的透视投影，有关详细信息，请参阅OpenGL
    // gluPerspective文档.宽高比定义为宽/高。
    getCamera()->setProjectionMatrixAsPerspective(
            30.0f, static_cast<double>(width()) /
                           static_cast<double>(height()),
            1.0f, 10000.0f);
    //设置GraphicsContext，提供用于管理与此相机相关联的OpenGL图形上下文的机制。
    getCamera()->setGraphicsContext(getGraphicsWindow());
    //设置渲染遍历将使用的线程模型。
    setThreadingModel(osgViewer::Viewer::SingleThreaded);
    //    //加载地图
    //    osg::ref_ptr<osg::Node> loadedMap =
    //    osgDB::readNodeFile(
    //            "/home/lzt/material/SimpleMap.osg");
    //    //加载UAV
    //    loadUAV();
    //    modelRoot = new osg::Group;
    //    addUAVStoModelRoot(modelRoot);
    //    //    NumUAV = modelRoot->getNumChildren();
    //    //加载HUD
    //    osgText::Text* text = new osgText::Text;
    //    //构建节点树
    //    osg::ref_ptr<osg::Group> root = new osg::Group;
    //    root->addChild(loadedMap.get());
    //    root->addChild(createHUD_viewPoint(text));
    //    root->addChild(modelRoot);
    //    //设置清屏颜色、事件操作等
    //    this->getCamera()->setClearColor(
    //            osg::Vec4(0.3, 0.3, 0.3, 0.3));
    //    this->setSceneData(root.get());
    //    this->setCameraManipulator(
    //            new MyHandler(modelRoot.get(), text));
    //    //并且把它的timeout()(定时器超时信号)连接到适当的槽。当这段时间过去了，它将会发射timeout()信号。
    //    connect(&_timer, SIGNAL(timeout()), this,
    //            SLOT(ViewerQT::changeUAVdof()));
    //    connect(&_timer, SIGNAL(timeout()), this,
    //            SLOT(updateGL()));
    //    _timer.start(20);  //使用start()来开始
}

// osgSim::DOFTransform* ViewerQT::initModel(
//        int color, char num[])
//{
//    UAV* glider = new UAV;
//    osg::ref_ptr<osg::Node> loadedModel =
//            glider->CreateGlider(color, num);
//    doft = new osgSim::DOFTransform;
//    doft->setCurrentScale(osg::Vec3(1.f, 1.f, 1.f));
//    doft->addChild(loadedModel.get());
//    doft->setName(num);
//    return doft;
//    delete glider;
//}

// void ViewerQT::loadUAV()
//{
//    doft1 = new osgSim::DOFTransform;
//    doft2 = new osgSim::DOFTransform;
//    doft3 = new osgSim::DOFTransform;
//    doft1 = initModel(4, "1");
//    doft2 = initModel(1, "2");
//    doft3 = initModel(3, "3");
//}

// void ViewerQT::addUAVStoModelRoot(osg::Group* modelRoot)
//{
//    modelRoot->addChild(doft1);
//    modelRoot->addChild(doft2);
//    modelRoot->addChild(doft3);
//}

// void ViewerQT::changeUAVdof()
//{
//    std::string fileName =
//            "/home/lzt/AllProjects/TeachersProject/"
//            "readroute/fmps_simu_result.dat";
//    //    if (argc > 1)
//    //    {
//    //        fileName = argv[1];
//    //    }

//    ifstream iReader;
//    iReader.open(fileName, std::ios::in |
//    std::ios::binary);
//    //    if (!iReader.is_open())
//    //    {
//    //        cout << "Error : Open file \'" + fileName +
//    //                        "\' failed."
//    //             << endl;
//    //    }

//    IstreamInputStream* pIStream =
//            new IstreamInputStream(&iReader);
//    CodedInputStream* pCodeStream =
//            new CodedInputStream(pIStream);

//    Arena arena;
//    uint32_t type;
//    unsigned num = modelRoot->getNumChildren();
//    osgSim::DOFTransform* temp = new osgSim::DOFTransform;

//    // First, read the len of object MpsPlane
//    for (unsigned i = 0; i <= num; i++)
//    {
//        while (pCodeStream->ReadVarint32(&type))
//        {
//            uint32_t len;
//            if (!pCodeStream->ReadVarint32(&len)) break;

//            string codeString;
//            if (!pCodeStream->ReadString(&codeString,
//            len))
//                break;

//            //            cout << std::fixed;
//            //            cout << "Type = " << setw(10) <<
//            //            type << ", "
//            //                 << "Len = " << setw(4) <<
//            len
//            //                 << ", ";

//            //            if (type >= 9000000 && type <=
//            //            9999999)
//            //            {
//            //                // Equip - Entity
//            //                MpsSEquip* pEquip =
//            // Arena::CreateMessage<MpsSEquip>(
//            //                                &arena);
//            // pEquip->ParseFromString(codeString);
//            //                printEquip(pEquip);
//            //            }
//            if (type >= 3000000000 && type <= 3999999999)
//            {
//                // UAV
//                MpsSPlane* pPlane =
//                        Arena::CreateMessage<MpsSPlane>(
//                                &arena);
//                pPlane->ParseFromString(codeString);
//                temp =
//                dynamic_cast<osgSim::DOFTransform*>(
//                        modelRoot->getChild(i));

//                changeUAV(pPlane, temp);
//            }
//        }
//    }
//    delete pCodeStream;
//    delete pIStream;

//    iReader.close();
//}

// void ViewerQT::changeUAV(
//        MpsSPlane* pPlane, osgSim::DOFTransform* temp)
//{
//    if (pPlane == nullptr) return;
//    //    const MpsSHeader& head = pPlane->head();
//    const MpsSPosition& pos = pPlane->pos();
//    temp->setCurrentTranslate(
//            osg::Vec3(pos.lng(), pos.lat(), pos.h()));
//}
