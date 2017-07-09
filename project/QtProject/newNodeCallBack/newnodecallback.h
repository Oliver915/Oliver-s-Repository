#ifndef NEWNODECALLBACK_H
#define NEWNODECALLBACK_H
#include <osg/MatrixTransform>
#include <osg/NodeCallback>

class newNodeCallBack : public osg::NodeCallback
{
public:
    newNodeCallBack();
    virtual void operator()(
            osg::Node* node, osg::NodeVisitor* nv);

private:

};

#endif  // NEWNODECALLBACK_H
