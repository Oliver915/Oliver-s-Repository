#include "pickhandler.h"

bool PickHandler::handle(
        const osgGA::GUIEventAdapter& ea,
        osgGA::GUIActionAdapter& aa)
{
    switch (ea.getEventType())
    {
        case (osgGA::GUIEventAdapter::PUSH):
        {
            osg::ref_ptr<osgViewer::Viewer> viewer =
                    dynamic_cast<osgViewer::Viewer*>(&aa);
            if (viewer)
            {
                pick(viewer, ea);
            }
            break;
        }
        default:
            return false;
    }
}

void PickHandler::pick(
        osgViewer::Viewer* viewer,
        const osgGA::GUIEventAdapter& ea)
{
    osgUtil::LineSegmentIntersector::Intersections
            intersections;
    if (viewer->computeIntersections(ea, intersections))
    {
        for (osgUtil::LineSegmentIntersector::
                     Intersections::iterator hitr =
                             intersections.begin();
             hitr != intersections.end(); ++hitr)
        {
            if (!hitr->nodePath.empty() &&
                !(hitr->nodePath.back()->getName().empty()))
            {
                _dofNode = new osgSim::DOFTransform;
                _dofNode =
                        dynamic_cast<osgSim::DOFTransform*>(
                                hitr->nodePath.back());
            }
        }
    }
}
