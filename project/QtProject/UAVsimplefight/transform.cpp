#include "transform.h"

Transform::Transform()
{

}
osg::ref_ptr<osg::Node> Transform::CreateGlider()
{
    osg::ref_ptr<osg::Node> glider = osgDB::readNodeFile(
            "/home/mengyu/material/"
            "gliderZoomIn.osg");
    GliderTrans = new osg::PositionAttitudeTransform();
    GLiderPath = new osg::AnimationPath;
    GLiderPath->insert(
            0, osg::AnimationPath::ControlPoint(
                       osg::Vec3(0.f, 0.f, 30.f)));
    GLiderPath->insert(
            20, osg::AnimationPath::ControlPoint(
                        osg::Vec3(50.f, 40.f, 70.f)));
    GliderTrans->setUpdateCallback(
            new osg::AnimationPathCallback(
                    GLiderPath, 0.0, 1.0));
    GliderTrans->addChild(glider);
    return GliderTrans;
}
