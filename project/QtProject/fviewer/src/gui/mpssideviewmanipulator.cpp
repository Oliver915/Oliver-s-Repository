#include "mpssideviewmanipulator.h"
#include <osgViewer/Viewer>
#include "mpsdatamanager.h"
#include "mpshudhandler.h"

MpsSideViewManipulator::MpsSideViewManipulator(
        MpsHUDHandler* pHandler)
    : uavDOF(nullptr)
    , hudHandler(pHandler)
    , x(0.0)
    , y(0.0)
    , z(0.0)
{
    // Default uavDOF(index == 1)
    uavDOF = MpsDataManager::instance()->findUAVByIndex(1);
    rotateFlag = false;
    sideViewFlag = false;
}

void MpsSideViewManipulator::init(
        const osgGA::GUIEventAdapter& eventAdapter,
        osgGA::GUIActionAdapter& actionAdapter)
{
    flushMouseEventStack();

    home(eventAdapter, actionAdapter);
    // stop animation
    _thrown = false;
    actionAdapter.requestContinuousUpdate(false);
}

bool MpsSideViewManipulator::handleKeyDown(
        const osgGA::GUIEventAdapter& eventAdapter,
        osgGA::GUIActionAdapter& actionAdapter)
{
    osgViewer::Viewer* viewer =
            dynamic_cast<osgViewer::Viewer*>(
                    &actionAdapter);
    if (viewer == nullptr) return false;

    // choose the uav
    if (eventAdapter.getKey() <= 51 &&
        eventAdapter.getKey() >= 49)
    {
        uavDOF = MpsDataManager::instance()->findUAVByIndex(
                eventAdapter.getKey() - 48);
        flushMouseEventStack();
        updateXYZ(uavDOF);
        this->setHomePosition(
                osg::Vec3(x - 1000, y, z + 100),
                uavDOF->getCurrentTranslate(), osg::Z_AXIS);
        _thrown = false;
        home(eventAdapter, actionAdapter);
    }

    // change the orientation of the camera behind the UAV
    if (eventAdapter.getKey() == 'b')
    {
        flushMouseEventStack();
        updateXYZ(uavDOF);
        this->setHomePosition(
                osg::Vec3(x, y - 1000, z + 100),
                uavDOF->getCurrentTranslate(), osg::Z_AXIS);
        _thrown = false;
        home(eventAdapter, actionAdapter);
        return true;
    }

    // change the orientation of the camera side the UAV
    if (eventAdapter.getKey() == 's' )
    {
        flushMouseEventStack();
        updateXYZ(uavDOF);
        this->setHomePosition(
                osg::Vec3(x - 1000, y, z + 100),
                uavDOF->getCurrentTranslate(), osg::Z_AXIS);
        _thrown = false;
        home(eventAdapter, actionAdapter);
        return true;
    }

    // yaw the camera
    if (eventAdapter.getKey() ==
        osgGA::GUIEventAdapter::KEY_0)
    {
        rotateWithFixedVertical(0.0, -0.01);
        return true;
    }

    // pitch the camera

    // make the camera ratate around the node
    if (eventAdapter.getKey() == 'o')
    {
        if (rotateFlag)
        {
            rotateFlag = false;
        }
        else
        {
            rotateFlag = true;
        }
    }

    // KEY_Spave make the camera return to home
    if (eventAdapter.getKey() ==
        osgGA::GUIEventAdapter::KEY_Space)
    {
        flushMouseEventStack();
        _thrown = false;
        home(eventAdapter, actionAdapter);
        return true;
    }

    return false;
}

bool MpsSideViewManipulator::handleChangeView(
        const osgGA::GUIEventAdapter& eventAdapter,
        osgGA::GUIActionAdapter& actionAdapter)
{
    if (sideViewFlag)
    {
        flushMouseEventStack();
        updateXYZ(uavDOF);
        this->setHomePosition(
                osg::Vec3(x - 1000, y, z + 100),
                uavDOF->getCurrentTranslate(), osg::Z_AXIS);
        _thrown = false;
        home(eventAdapter, actionAdapter);
        return true;
        sideViewFlag = false;
    }

}

bool MpsSideViewManipulator::handleFrame(
        const osgGA::GUIEventAdapter& eventAdapter,
        osgGA::GUIActionAdapter& actionAdapter)
{
    StandardManipulator::handleFrame(
            eventAdapter, actionAdapter);

    Q_ASSERT(hudHandler != nullptr);
    hudHandler->updateText(uavDOF);

    if (uavDOF)
    {
        setTrackNode(uavDOF->getChild(0));
    }

    if (rotateFlag)
    {
        rotateWithFixedVertical(0.001, 0.0);
    }

    return false;
}

void MpsSideViewManipulator::updateXYZ(
        osg::ref_ptr<osgSim::DOFTransform> uavDOF)
{
    x = uavDOF->getCurrentTranslate().x();
    y = uavDOF->getCurrentTranslate().y();
    z = uavDOF->getCurrentTranslate().z();
}

void MpsSideViewManipulator::changeUAVthroughBar(
        int indexOfUAV)
{
    uavDOF = MpsDataManager::instance()->findUAVByIndex(
            indexOfUAV);
}

void MpsSideViewManipulator::clickZoom(
        const float dy, bool pushForwardIfNeeded)
{
    OrbitManipulator::zoomModel(dy, pushForwardIfNeeded);
}

void MpsSideViewManipulator::clickSideView()
{
    sideViewFlag = true;
}
