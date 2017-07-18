#include "myhandler.h"
#include <osgGA/GUIEventAdapter>

bool MyHandler::handleKeyDown(
        const osgGA::GUIEventAdapter& ea,
        osgGA::GUIActionAdapter& aa)
{
    //    osgViewer::Viewer* viewer =
    //            dynamic_cast<osgViewer::Viewer*>(&aa);
    if (!_model) return false;
    //    osg::Matrix matrix = _model->getMatrix();
    //    osg::Vec3 v;
    findNodeVisitor findUAVNode("UAV");
    _model->accept(findUAVNode);
    osgSim::DOFTransform* uavDOF =
            dynamic_cast<osgSim::DOFTransform*>(
                    findUAVNode.getFirst());
    switch (ea.getKey())
    {
        case 'a':
        case 'A':
            if (uavDOF)
            {
                uavDOF->setCurrentTranslate(osg::Vec3(
                        50.f, 50.f, 50.f));
            }
            break;
        case 'd':
        case 'D':
            if (uavDOF)
            {
                uavDOF->setCurrentHPR(
                        osg::Vec3(3.14159 / 4.0, 0.f, 0.f));
            }
            break;
        case 'w':
        case 'W':
            if (uavDOF)
            {
                uavDOF->setCurrentHPR(
                        osg::Vec3(0.f, 3.14159 / 4.0, 0.f));
            }
            break;
        case 's':
        case 'S':
            if (uavDOF)
            {
                uavDOF->setCurrentHPR(osg::Vec3(
                        0.f, -3.14159 / 4.0, 0.f));
            }
            break;
        case 'j':
        case 'J':
            if (uavDOF)
            {
                uavDOF->setCurrentHPR(osg::Vec3(
                        0.f, 0.f, -3.14159 / 4.0));
            }
            break;
        case 'k':
        case 'K':
            if (uavDOF)
            {
                uavDOF->setCurrentHPR(
                        osg::Vec3(0.f, 0.f, 3.14159 / 4.0));
            }
            break;
        case osgGA::GUIEventAdapter::KEY_Space:
            flushMouseEventStack();
            _thrown = false;
            home(ea, aa);
            return true;
            break;
        //        case '1':
        //            v =
        //            getBoundingBoxPosition(_model.get());
        //            cout << v.x() << " , " << v.y() << " ,
        //            "
        //                 << v.z() << endl;
        //            break;
        default:
            break;
    }
    return false;
}

// osg::Vec3 MyHandler::getBoundingBoxPosition(
//        osg::MatrixTransform* mt)
//{
//    osg::BoundingSphere pcenter = mt->getBound();
//    osg::Vec3 vec = pcenter.center();
//    return vec;
//}
