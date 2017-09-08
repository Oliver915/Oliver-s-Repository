#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMap>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <osg/TexEnv>
#include <osg/TexGen>
#include <osg/Texture2D>
#include <osgGA/KeySwitchMatrixManipulator>
#include <osgGA/NodeTrackerManipulator>
#include <osgSim/DOFTransform>
#include <osgViewer/ViewerEventHandlers>
#include <string>
#include "google/protobuf/io/zero_copy_stream_impl.h"
#include "math.h"
#include "mps_coordinate.pb.h"
#include "myhandler.h"
#include "trailercallback.h"
#include "ui_mainwindow.h"
#include "viewerqt.h"

using google::protobuf::io::IstreamInputStream;
using google::protobuf::io::CodedInputStream;
using google::protobuf::Arena;

namespace Ui {
class MainWindow;
}

/**
 * @brief The MainWindow class
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    /**
     * @brief MainWindow
     * @param parent
     */
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();

    /**
     * @brief 通过传入参数构建并初始化带编号的无人机模型
     * @param index
     * @param color
     * @return
     */
    osg::ref_ptr<osgSim::DOFTransform> CreateUAV(
            std::string index, int color, osg::Node* UAV);

    /**
     * @brief changeUAV
     * @param pPlane
     * @param temp
     */
    void changeUAV(
            MpsSPlane* pPlane, osgSim::DOFTransform* pUAV);

    /**
     * @brief 构建HUD
     * @param text
     * @return
     */
    osg::Node* createHUD_viewPoint(osgText::Text* text);

    /**
     * @brief createRibbon
     * @param colorRGB
     * @return
     */
    osg::Geometry* createRibbon(const osg::Vec3& colorRGB);

public slots:
    /**
     * @brief changeUAVdof
     */
    void changeUAVdof();

private:
    // UI
    Ui::MainWindow* ui;

    // Update timer
    QTimer updateTimer;

    // OSG model root
    osg::Group* modelRoot;

    // Input stream for simu data
    IstreamInputStream* pIStream;
    CodedInputStream* pCodeStream;
    std::ifstream iReader;

    // id -> UAV
    ID2UAVMap id_uav_map;

    // osg viewer
    ViewerQT* viewerWindow;
};

#endif  // MAINWINDOW_H
