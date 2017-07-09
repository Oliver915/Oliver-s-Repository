//#include "pickhandler.h"

//bool PickHandler::handle(
//        const osgGA::GUIEventAdapter& ea,
//        osgGA::GUIActionAdapter& aa)
//{
//    osg::ref_ptr<osgViewer::Viewer> viewer =
//            dynamic_cast<osgViewer::Viewer*>(&aa);
//    if (!viewer) return false;
//    switch (ea.getEventType())
//    {
//        case (osgGA::GUIEventAdapter::PUSH):
//        {
//            _mX = ea.getX();
//            _mY = ea.getY();
//            pick(viewer.get(), ea.getX(), ea.getY());
//            break;
//        }
//        case (osgGA::GUIEventAdapter::RELEASE):
//        {
//            if (_mX == ea.getX() && _mY == ea.getY())
//            {
//                pick(viewer.get(), ea.getX(), ea.getY());
//            }
//            break;
//        }
//        default:
//            break;
//    }
//    return false;
//}

//void PickHandler::pick(
//        osg::ref_ptr<osgViewer::Viewer> viewer, float x,
//        float y )
//{
//    osg::ref_ptr<osg::Node> node = new osg::Node();
//    osg::ref_ptr<osg::Group> parent = new osg::Group();
//    osgUtil::LineSegmentIntersector::Intersections
//            intersections;
//    if (viewer->computeIntersections(x, y, intersections))
//    {
//        osgUtil::LineSegmentIntersector::Intersection
//                intersection = *intersections.begin();
//        osg::NodePath& nodePath = intersection.nodePath;
//        node = (nodePath.size() >= 1) ?
//                       nodePath[nodePath.size() - 1] :
//                       0;
//        parent = (nodePath.size() >= 2) ?
//                         dynamic_cast<osg::Group*>
//                                 (nodePath
//                                         [nodePath.size() -
//                                          2]) :
//                         0;
//    }

//}
