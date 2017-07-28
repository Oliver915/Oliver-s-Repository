#ifndef UAV_H
#define UAV_H

#include <osg/AnimationPath>
#include <osg/Geometry>
#include <osg/Group>
#include <osg/MatrixTransform>
#include <osg/Multisample>
#include <osg/NodeCallback>
#include <osg/PositionAttitudeTransform>
#include <osg/TexEnv>
#include <osg/TexGen>
#include <osg/Texture2D>
#include <osgAnimation/Animation>
#include <osgAnimation/BasicAnimationManager>
#include <osgAnimation/StackedScaleElement>
#include <osgAnimation/StackedTranslateElement>
#include <osgAnimation/UpdateMatrixTransform>
#include <osgDB/ReadFile>
#include <osgSim/DOFTransform>
#include <osgText/Font>
#include <osgText/Text>
#include <string>
using namespace std;

class UAV : public osg::Node
{
public:
    UAV();
    virtual ~UAV() {}
    osg::ref_ptr<osg::Node> CreateGlider(
            int color, string index);

protected:
    osg::ref_ptr<osg::PositionAttitudeTransform> LineTrans;
    osg::ref_ptr<osg::AnimationPath> GLiderPath;
    osg::ref_ptr<osg::AnimationPath> LinePath;
    osg::ref_ptr<osg::Group> LineGroup;
};

#endif  // UAV_H
