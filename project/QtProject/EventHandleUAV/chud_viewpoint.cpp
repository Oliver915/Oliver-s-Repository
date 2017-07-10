#include "chud_viewpoint.h"
using namespace std;

bool CHUD_viewPoint::handle(
        const osgGA::GUIEventAdapter& ea,
        osgGA::GUIActionAdapter& aa)
{
    if (!m_model) return false;
    switch (ea.getEventType())
    {
        case osgGA::GUIEventAdapter::FRAME:
        {
            osgViewer::Viewer* viewer =
                    dynamic_cast<osgViewer::Viewer*>(&aa);
            if (viewer)
            {
                osg::Vec3 v;
                v = getBoundingBoxPosition(m_model);
                UpdateText(v, ea);
            }
            return true;
        }
        default:
            return false;
    }
}
osg::Vec3 CHUD_viewPoint::getBoundingBoxPosition(
        osg::MatrixTransform* mt)
{
    osg::BoundingSphere pcenter = mt->getBound();
    osg::Vec3 vec = pcenter.center();
    return vec;
}

void CHUD_viewPoint::UpdateText(
        const osg::Vec3f& v, const osgGA::GUIEventAdapter&)
{
    std::string InfoStr = "";
    std::ostringstream os;
    os << "Position( X: " << v.x() << "  y: " << v.y()
       << "  z: " << v.z() << ")";
    InfoStr = os.str();
    setLabel(InfoStr);
}
