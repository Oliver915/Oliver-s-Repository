#ifndef NEWNODECALLBACK_H
#define NEWNODECALLBACK_H
#include <osg/NodeCallback>
#include <osg/MatrixTransform>

class newNodeCallBack : public osg::NodeCallback
{
public:
    newNodeCallBack(osg::Vec3 * v);
    virtual void operator()(
            osg::Node* node, osg::NodeVisitor* nv);

private:
    float h;
    float scale;
    osg::Vec3* vec;
};

#endif  // NEWNODECALLBACK_H
