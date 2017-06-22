#include <stdlib.h>
#include <iostream>
#include <osg/ComputeBoundsVisitor>
#include <osg/MatrixTransform>
using namespace std;

osg::Vec3 getBoundingBoxPosition(osg::Node* node)
{
    osg::BoundingSphere pcenter = node->getBound();
    osg::Vec3 vec = pcenter.center();
    //    osg::ComputeBoundsVisitor boundVisitor;
    //    node->accept(boundVisitor);
    //    osg::BoundingBox boundingBox =
    //            boundVisitor.getBoundingBox();
    cout << vec.x() << " , " << vec.y() << " , " << vec.z()
         << endl;
    //    osg::Vec3 vec;
    //    vec = boundingBox.center();

    //    return vec;
    return vec;
}
void initBoundingBoxPosition(osg::MatrixTransform* mt)
{
    osg::Vec3 vec = getBoundingBoxPosition(mt);
    mt->setMatrix(osg::Matrix::translate(-vec));
}
