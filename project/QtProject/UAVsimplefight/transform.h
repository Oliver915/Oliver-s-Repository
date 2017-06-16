#ifndef TRANSFORM_H
#define TRANSFORM_H

#include <osg/AnimationPath>
#include <osg/Geometry>
#include <osg/Node>
#include <osg/PositionAttitudeTransform>
#include <osg/TexEnv>
#include <osg/TexGen>
#include <osg/Texture2D>
#include <osgDB/ReadFile>

class Transform : public osg::Node
{
public:
    Transform();
    virtual ~Transform() {}
    osg::ref_ptr<osg::Node> CreateGlider(float x1, float y1, float z1, float x2,
            float y2, float z2, int a);

protected:
    osg::ref_ptr<osg::PositionAttitudeTransform>
            GliderTrans;
    osg::ref_ptr<osg::AnimationPath> GLiderPath;
};

#endif  // TRANSFORM_H
