#include "myhandler.h"
#include <osgGA/GUIEventAdapter>

bool MyHandler::handleKeyDown(
        const osgGA::GUIEventAdapter& ea,
        osgGA::GUIActionAdapter& aa)
{
    osgViewer::Viewer* viewer =
            dynamic_cast<osgViewer::Viewer*>(&aa);
    if (!_model) return false;
    //    osg::Matrix matrix = _model->getMatrix();
    //    osg::Vec3 v;
    //    findNodeVisitor findUAVNode("1");
    //    _model->accept(findUAVNode);
    //    osgSim::DOFTransform* _uavDOF =
    //            dynamic_cast<osgSim::DOFTransform*>(
    //                    findUAVNode.getFirst());

    osg::Vec3 v;
    switch (ea.getKey())
    {
        if (viewer)
        {
            case 'a':
            case 'A':
                if (_uavDOF)
                {
                    _uavDOF->setCurrentHPR(osg::Vec3(
                            -3.14159 / 4.0, 0.f, 0.f));
                }
                break;
            case 'd':
            case 'D':
                if (_uavDOF)
                {
                    _uavDOF->setCurrentHPR(osg::Vec3(
                            3.14159 / 4.0, 0.f, 0.f));
                }
                break;
            case 'w':
            case 'W':
                if (_uavDOF)
                {
                    _uavDOF->setCurrentHPR(osg::Vec3(
                            0.f, 3.14159 / 4.0, 0.f));
                }
                break;
            case 's':
            case 'S':
                if (_uavDOF)
                {
                    _uavDOF->setCurrentHPR(osg::Vec3(
                            0.f, -3.14159 / 4.0, 0.f));
                }
                break;
            case 'j':
            case 'J':
                if (_uavDOF)
                {
                    _uavDOF->setCurrentHPR(osg::Vec3(
                            0.f, 0.f, -3.14159 / 4.0));
                }
                break;
            case 'k':
            case 'K':
                if (_uavDOF)
                {
                    _uavDOF->setCurrentHPR(osg::Vec3(
                            0.f, 0.f, 3.14159 / 4.0));
                }
                break;
            case '1':
            {
                findNodeVisitor findUAVNode1("1");
                _model->accept(findUAVNode1);
                _uavDOF =
                        dynamic_cast<osgSim::DOFTransform*>(
                                findUAVNode1.getFirst());
                _uavDOF->setCurrentTranslate(
                        osg::Vec3(50.f, 50.f, 50.f));
                break;
            }
            case '2':
            {
                findNodeVisitor findUAVNode2("2");
                _model->accept(findUAVNode2);
                _uavDOF =
                        dynamic_cast<osgSim::DOFTransform*>(
                                findUAVNode2.getFirst());
                _uavDOF->setCurrentTranslate(
                        osg::Vec3(-50.f, -50.f, 50.f));
                break;
            }
            case '3':
            {
                findNodeVisitor findUAVNode3("3");
                _model->accept(findUAVNode3);
                _uavDOF =
                        dynamic_cast<osgSim::DOFTransform*>(
                                findUAVNode3.getFirst());
                _uavDOF->setCurrentTranslate(
                        osg::Vec3(80.f, -10.f, 50.f));
                break;
            }
            case osgGA::GUIEventAdapter::KEY_Space:
                flushMouseEventStack();
                _thrown = false;
                home(ea, aa);
                return true;
                break;

            default:
                break;
        }
        return false;
    }
    return false;
}

bool MyHandler::handleFrame(
        const osgGA::GUIEventAdapter& ea,
        osgGA::GUIActionAdapter& aa)
{
    StandardManipulator::handleFrame(ea, aa);
    UpdateText(ea, _uavDOF);
    return false;
}

void MyHandler::UpdateText(
        const osgGA::GUIEventAdapter&,
        const osgSim::DOFTransform* doft)
{
    std::string InfoStr = "";
    std::ostringstream os;
    os << "Name : " << doft->getName() << endl
       << endl
       << "X : " << doft->getCurrentTranslate().x() << endl
       << endl
       << "Y : " << doft->getCurrentTranslate().y() << endl
       << endl
       << "Z : " << doft->getCurrentTranslate().z() << endl
       << endl
       << "Heading : " << doft->getCurrentHPR().x() << endl
       << endl
       << "Pitch : " << doft->getCurrentHPR().y() << endl
       << endl
       << "Rolling : " << doft->getCurrentHPR().z();
    InfoStr = os.str();
    setLabel(InfoStr);
}

// osg::Vec3 MyHandler::getBoundingBoxPosition(
//        osg::MatrixTransform* mt)
//{
//    osg::BoundingSphere pcenter = mt->getBound();
//    osg::Vec3 vec = pcenter.center();
//    return vec;
//}
