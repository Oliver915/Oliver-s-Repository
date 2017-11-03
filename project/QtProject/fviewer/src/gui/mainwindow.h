#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <osgSim/DOFTransform>
#include "google/protobuf/io/zero_copy_stream_impl.h"
#include "inputdialog.h"
#include "mps_coordinate.pb.h"
#include "mpshudhandler.h"
#include "viewerqt.h"
#include "mpssideviewmanipulator.h"
#include "mpstrackballmanipulator.h"

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

private:
    /**
     * @brief create and init UAV with the parameters gived
     * @param index
     * @param color
     * @return
     */
    osgSim::DOFTransform* createUAV(
            std::string index, int color);

    /**
     * @brief transformLatAndLonToXYZ
     * @param pPlane
     * @return
     */
    osg::Vec3 transformLatAndLonToXYZ(MpsSPlane* pPlane);

    /**
     * @brief changeUAV
     * @param pPlane
     * @param temp
     */
    void changeUAV(
            MpsSPlane* pPlane, osgSim::DOFTransform* pUAV);

    /**
     * @brief create HUD
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

    /**
     * @brief addGeometryToGeode
     * @param geometryTrack
     * @param geodeTrack
     */
    void addGeometryToGeode(
            osg::Geometry* geometryTrack,
            osg::Geode* geodeTrack);

    /**
     * @brief createMenuBar
     */
    void createMenuBar();

    /**
     * @brief createToolBar
     */
    void createToolBar();

public slots:
    /**
     * @brief changeUAVdof
     */
    void changeUAVdof();

    /**
     * @brief clickUAV
     */
    void clickUAV();

    /**
     * @brief clickShow
     */
    void clickShow();

    /**
     * @brief clickHide
     */
    void clickHide();

    /**
     * @brief clickZoomIn
     */
    void clickZoomIn();

    /**
     * @brief clickZoomOut
     */
    void clickZoomOut();

    /**
     * @brief clickSideView
     */
    void clickSideView();


private:
    // UI
    Ui::MainWindow* ui;

    // Update timer
    QTimer updateTimer;

    // OSG ROOT
    osg::Group* root;

    // OSG model root
    osg::Group* modelRoot;

    // Input stream for simu data
    IstreamInputStream* pIStream;
    CodedInputStream* pCodeStream;
    std::ifstream iReader;

    // osg viewer
    ViewerQT* viewerWindow;

    osg::Geode* textGeode;
    // HUD handler
    MpsHUDHandler* pHUDHandler;

    // MpsTrackballManipulator
    MpsTrackballManipulator* pTrackballManipulator;

    // SideViewManipulator
    MpsSideViewManipulator* pSideView;

    // manu
    QMenu* menu[10];

    // manuBar
    QMenuBar* menuBar;
    QAction* searchUAV;

    // toolBar
    QAction* hideAction;
    QAction* showAction;
    QToolBar* fileToolBar;

    // inputDialog
    InputDialog* inputDlg;
};

#endif  // MAINWINDOW_H
