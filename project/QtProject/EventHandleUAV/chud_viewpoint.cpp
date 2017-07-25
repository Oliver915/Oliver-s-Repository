#include "chud_viewpoint.h"
using namespace std;

bool CHUD_viewPoint::handle(
        const osgGA::GUIEventAdapter& ea,
        osgGA::GUIActionAdapter& aa)
{
    osgViewer::Viewer* viewer =
            dynamic_cast<osgViewer::Viewer*>(&aa);
    switch (ea.getEventType())
    {
        case osgGA::GUIEventAdapter::FRAME:
        {
            if (viewer)
            {
                osg::Vec3 v;

                v = getBoundingBoxPosition(m_model);
                UpdateText(v, ea, m_model);
            }
            return false;
        }
//        case osgGA::GUIEventAdapter::PUSH:
//        {
//            if (viewer)
//            {

//                    m_model = dynamic_cast<
//                            osgSim::DOFTransform*>(
//                            pick(viewer, ea));
//                return false;
//            }
//            return false;
//        }
        default:
            return false;
    }
}
osg::Vec3 CHUD_viewPoint::getBoundingBoxPosition(
        osgSim::DOFTransform* doft)
{
    osg::BoundingSphere pcenter = doft->getBound();
    osg::Vec3 vec = pcenter.center();
    return vec;
}

void CHUD_viewPoint::UpdateText(
        const osg::Vec3f& v, const osgGA::GUIEventAdapter&,
        const osgSim::DOFTransform* doft)
{
    std::string InfoStr = "";
    std::ostringstream os;
    os << "Name : " << doft->getName() << endl
       << endl
       << "X : " << v.x() << endl
       << endl
       << "Y : " << v.y() << endl
       << endl
       << "Z : " << v.z() << endl
       << endl
       << "Heading : " << endl
       << endl
       << "Pitch : " << endl
       << endl
       << "Rolling : ";
    InfoStr = os.str();
    setLabel(InfoStr);
}

//osg::Node* CHUD_viewPoint::pick(
//        osgViewer::Viewer* viewer,
//        const osgGA::GUIEventAdapter& ea)
//{
//    osg::ref_ptr<osgUtil::LineSegmentIntersector>
//            intersector =
//                    new osgUtil::LineSegmentIntersector(
//                            osgUtil::Intersector::WINDOW,
//                            ea.getX(), ea.getY());
//    osgUtil::IntersectionVisitor iv(intersector.get());
//    iv.setTraversalMask(~0x1);
//    viewer->getCamera()->accept(iv);
//    if (intersector->containsIntersections())
//    {
//        osgUtil::LineSegmentIntersector::Intersection
//                result = *(intersector->getIntersections()
//                                   .begin());
//        return result.nodePath.front();
//    }
//    //    osgUtil::LineSegmentIntersector::Intersections
//    //            intersections;
//    //    if (viewer->computeIntersections(ea,
//    //    intersections))
//    //    {
//    //        for (osgUtil::LineSegmentIntersector::
//    //                     Intersections::iterator hitr =
//    //                             intersections.begin();
//    //             hitr != intersections.end(); ++hitr)
//    //        {
//    //            if (!hitr->nodePath.empty() &&
//    //                !(hitr->nodePath.back()->getName().empty()))
//    //                return hitr->nodePath.back();
//    //        }
//    //    }
//}
