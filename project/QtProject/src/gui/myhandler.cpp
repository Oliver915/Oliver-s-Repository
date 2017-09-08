#include "myhandler.h"

using std::endl;

// const
static const double ANGLE = 180 / 3.1415926;
static const double TEMP = 180 / 20037508.34;

MyHandler::MyHandler(
        osgText::Text* txt, ID2UAVMap* id_uavmyMap)
    : uavDOF(new osgSim::DOFTransform)
    , text(txt)
    , pID2UAVMap(id_uavmyMap)
{
    uavDOF = id_uavmyMap->begin().value();
}

bool MyHandler::handleKeyDown(
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
        ID2UAVMap::const_iterator itor =
                pID2UAVMap->begin() +
                (eventAdapter.getKey() - 49);
        uavDOF = itor.value();
    }

    //空格键使得相机回到home处
    if (eventAdapter.getKey() ==
        osgGA::GUIEventAdapter::KEY_Space)
    {
        flushMouseEventStack();
        _thrown = false;
        home(eventAdapter, actionAdapter);
        return true;
    }

    //键盘A键
    if (eventAdapter.getKey() ==
        osgGA::GUIEventAdapter::KEY_A)
    {
        flushMouseEventStack();
        _thrown = false;
        performMovementLeftKey(0.f, -0.005f, 0.f);
        actionAdapter.requestRedraw();
    }

    //键盘D键
    if (eventAdapter.getKey() ==
        osgGA::GUIEventAdapter::KEY_D)
    {
        flushMouseEventStack();
        _thrown = false;
        performMovementLeftKey(0.f, 0.005f, 0.f);
        actionAdapter.requestRedraw();
    }

    //键盘W键
    if (eventAdapter.getKey() ==
        osgGA::GUIEventAdapter::KEY_W)
    {
        flushMouseEventStack();
        _thrown = false;
        performMovementLeftKey(0.f, 0.0f, 0.005f);
        actionAdapter.requestRedraw();
    }

    //键盘S键
    if (eventAdapter.getKey() ==
        osgGA::GUIEventAdapter::KEY_S)
    {
        flushMouseEventStack();
        _thrown = false;
        performMovementLeftKey(0.f, 0.0f, -0.005f);
        actionAdapter.requestRedraw();
    }

    return false;
}

bool MyHandler::handleFrame(
        const osgGA::GUIEventAdapter& eventAdapter,
        osgGA::GUIActionAdapter& actionAdapter)
{
    StandardManipulator::handleFrame(
            eventAdapter, actionAdapter);
    UpdateText(eventAdapter, uavDOF);

    return false;
}

void MyHandler::setLabel(const std::string& name)
{
    if (text.get()) text->setText(name);
}

void MyHandler::UpdateText(
        const osgGA::GUIEventAdapter& eventAdapter,
        const osgSim::DOFTransform* doft)
{
    double y = doft->getCurrentTranslate().y() + 1450000;
    double latitude =
            (360 / 3.1415926) *
                    atan(exp(
                            y * (3.1415926 / 180) * TEMP)) -
            90;

    std::ostringstream os;
    os << "Name : " << doft->getName() << endl
       << endl
       << "Longtitude : " << std::setprecision(10)
       << (doft->getCurrentTranslate().x() + 4950000) * TEMP
       << endl
       << endl
       << "Latitude : " << latitude << endl
       << endl
       << std::setprecision(6)
       << "Height : " << doft->getCurrentTranslate().z()
       << endl
       << endl
       << "Heading : "
       << doft->getCurrentHPR().x() * (-ANGLE) << endl
       << endl
       << "Pitch : " << doft->getCurrentHPR().y() * ANGLE
       << endl
       << endl
       << "Rolling : " << doft->getCurrentHPR().z() * ANGLE;

    setLabel(os.str());
}

//键盘ADWS键控制视角的yaw、pitch角
bool MyHandler::performMovementLeftKey(
        double eventTimeDelta, double dx, double dy)
{
    // rotate camera
    if (getVerticalAxisFixed())
        rotateWithFixedVertical(dx, dy);
    else
    {
        rotateTrackball(
                0.f, 0.f, dx, dy,
                getThrowScale(eventTimeDelta));
    }
    return true;
}
