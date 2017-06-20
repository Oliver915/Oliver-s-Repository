#ifndef SCALECALLBACK_H
#define SCALECALLBACK_H
#include <osg/NodeCallback>
#include <osg/PositionAttitudeTransform>
class ScaleCallBack:public osg::NodeCallback
{
public:
    ScaleCallBack(float a);
    virtual void operator()(
            osg::Node* node, osg::NodeVisitor* nv);

private:
    float scale;
    float dscale;
};

#endif  // SCALECALLBACK_H
