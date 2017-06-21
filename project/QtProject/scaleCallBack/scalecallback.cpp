#include "scalecallback.h"

ScaleCallBack::ScaleCallBack(float a)
    : scale(1.0f)
{
    dscale = a;
}
void ScaleCallBack::operator()(
        osg::Node* node, osg::NodeVisitor* nv)
{
    osg::PositionAttitudeTransform* pat =
            dynamic_cast<osg::PositionAttitudeTransform*>(
                    node);
    if (pat)
    {
        pat->setScale(osg::Vec3(1.0f, 1.0f, scale));

        scale += dscale;
    }

    traverse(node, nv);
}
