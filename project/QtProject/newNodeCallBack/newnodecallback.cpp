#include "newnodecallback.h"
#include <unistd.h>
osg::Vec3 getBoundingBoxPosition(osg::Node* node);

newNodeCallBack::newNodeCallBack() {}

void newNodeCallBack::operator()(
        osg::Node* node, osg::NodeVisitor* nv)
{
    osg::Vec3 vec = getBoundingBoxPosition(node);
    osg::ref_ptr<osg::MatrixTransform> mt =
            dynamic_cast<osg::MatrixTransform*>(node);
    if (mt)
    {

        mt->setMatrix(osg::Matrix::translate(vec));
        mt->setMatrix(osg::Matrix::translate(-vec));
    }

    traverse(node, nv);
}
