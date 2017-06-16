#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <osg/AnimationPath>
#include <osg/Node>
#include <osg/PositionAttitudeTransform>
#include <osgDB/ReadFile>


class Transform : public osg::Node
{
public:
    Transform();
    virtual ~Transform() {}
    osg::ref_ptr<osg::Node> CreateGlider ();

protected:
    osg::ref_ptr<osg::PositionAttitudeTransform>
            GliderTrans;
    osg::ref_ptr<osg::AnimationPath> GLiderPath;
};

#endif  // TRANSFORM_H
