#ifndef MYHANDLER_H
#define MYHANDLER_H
#include <QMap>
#include <iomanip>
#include <iostream>
#include <osg/MatrixTransform>
#include <osgGA/GUIActionAdapter>
#include <osgGA/GUIEventHandler>
#include <osgGA/TrackballManipulator>
#include <osgSim/DOFTransform>
#include <osgText/Text>
#include <osgViewer/Viewer>
#include <sstream>
#include "google/protobuf/io/zero_copy_stream_impl.h"
#include "mps_coordinate.pb.h"

typedef QMap<uint32_t, osgSim::DOFTransform*> ID2UAVMap;

// OSG的事件控制类（鼠标、键盘、Frame等事件）
class MyHandler : public osgGA::TrackballManipulator
{
public:
    /**
     * @brief MyHandler
     * @param node
     * @param txt
     * @param id_uavmyMap
     */
    MyHandler(osgText::Text* txt, ID2UAVMap* id_uavmyMap);
    ~MyHandler() {}
    /**
     * @brief handleKeyDown
     * @param ea
     * @param aa
     * @return
     */
    virtual bool handleKeyDown(
            const osgGA::GUIEventAdapter& ea,
            osgGA::GUIActionAdapter& aa);

    /**
     * @brief handleFrame
     * @param ea
     * @param aa
     * @return
     */
    virtual bool handleFrame(
            const osgGA::GUIEventAdapter& ea,
            osgGA::GUIActionAdapter& aa);

    /**
     * @brief setLabel
     * @param name
     */
    void setLabel(const std::string& name);

    /**
     * @brief UpdateText
     * @param doft
     */
    void UpdateText(
            const osgGA::GUIEventAdapter&,
            const osgSim::DOFTransform* doft);

    /**
     * @brief performMovementLeftKey
     * @param eventTimeDelta
     * @param dx
     * @param dy
     * @return
     */
    bool performMovementLeftKey(
            double eventTimeDelta, double dx, double dy);

protected:
    //无人机节点
    osg::ref_ptr<osgSim::DOFTransform> uavDOF;

    // HUD数据栏文本节点
    osg::ref_ptr<osgText::Text> text;

    // map（id(key),uav(value))
    ID2UAVMap* pID2UAVMap;
};

#endif  // MYHANDLER_H
