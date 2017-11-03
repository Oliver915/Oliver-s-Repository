#include "mpstrackballmanipulator.h"
#include <osgViewer/Viewer>
#include "mpsdatamanager.h"
#include "mpshudhandler.h"

MpsTrackballManipulator::MpsTrackballManipulator(
        MpsHUDHandler* pHandler)
    : uavDOF(nullptr)
    , hudHandler(pHandler)
{
    // Default uavDOF(index == 1)
    uavDOF = MpsDataManager::instance()->findUAVByIndex(1);
}

bool MpsTrackballManipulator::handleKeyDown(
        const osgGA::GUIEventAdapter& eventAdapter,
        osgGA::GUIActionAdapter& actionAdapter)
{
    osgViewer::Viewer* viewer =
            dynamic_cast<osgViewer::Viewer*>(
                    &actionAdapter);
    if (viewer == nullptr) return false;

    if (eventAdapter.getKey() <= 51 &&
        eventAdapter.getKey() >= 49)
    {
        uavDOF = MpsDataManager::instance()->findUAVByIndex(
                eventAdapter.getKey() - 48);
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

    // KEY_A turn left(fine tuning)
    if (eventAdapter.getKey() ==
        osgGA::GUIEventAdapter::KEY_A)
    {
        flushMouseEventStack();
        _thrown = false;
        performMovementLeftKey(0.f, -0.00005f, 0.f);
        actionAdapter.requestRedraw();
    }

    // KEY_D turn right
    if (eventAdapter.getKey() ==
        osgGA::GUIEventAdapter::KEY_D)
    {
        flushMouseEventStack();
        _thrown = false;
        performMovementLeftKey(0.f, 0.00005f, 0.f);
        actionAdapter.requestRedraw();
    }

    // KEY_W turn up
    if (eventAdapter.getKey() ==
        osgGA::GUIEventAdapter::KEY_W)
    {
        flushMouseEventStack();
        _thrown = false;
        performMovementLeftKey(0.f, 0.0f, 0.00005f);
        actionAdapter.requestRedraw();
    }

    // KEY_S turn down
    if (eventAdapter.getKey() ==
        osgGA::GUIEventAdapter::KEY_S)
    {
        flushMouseEventStack();
        _thrown = false;
        performMovementLeftKey(0.f, 0.0f, -0.00005f);
        actionAdapter.requestRedraw();
    }

    return false;
}

bool MpsTrackballManipulator::handleFrame(
        const osgGA::GUIEventAdapter& eventAdapter,
        osgGA::GUIActionAdapter& actionAdapter)
{
    StandardManipulator::handleFrame(
            eventAdapter, actionAdapter);

    Q_ASSERT(hudHandler != nullptr);
    hudHandler->updateText(uavDOF);

    return false;
}

bool MpsTrackballManipulator::performMovementLeftKey(
        double eventTimeDelta, double dx, double dy)
{
    // rotate camera
    if (getVerticalAxisFixed())
    {
        rotateWithFixedVertical(dx, dy);
    }
    else
    {
        rotateTrackball(
                0.f, 0.f, dx, dy,
                getThrowScale(eventTimeDelta));
    }
    return true;
}

void MpsTrackballManipulator::changeUAVthroughBar(
        int indexOfUAV)
{
    uavDOF = MpsDataManager::instance()->findUAVByIndex(
            indexOfUAV);
}
