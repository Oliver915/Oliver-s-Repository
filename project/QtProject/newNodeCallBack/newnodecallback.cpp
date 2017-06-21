#include "newnodecallback.h"

newNodeCallBack::newNodeCallBack(osg::Vec3* v)
    : h(0)
{
    vec = v;
}

void newNodeCallBack::operator()(
        osg::Node* node, osg::NodeVisitor* nv)
{
    osg::ref_ptr<osg::MatrixTransform> mt =
            dynamic_cast<osg::MatrixTransform*>(node);
    if (mt)
    {
        mt->setMatrix(osg::Matrix::translate(
                vec->x(), vec->y(), vec->z() + h));
        h += 0.01;
    }

    traverse(node, nv);
}
