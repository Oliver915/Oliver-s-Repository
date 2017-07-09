#include <newnodecallback.h>
#include <stdlib.h>
#include <sys/time.h>
#include <unistd.h>
#include <QCoreApplication>
#include <iostream>
#include <osg/ComputeBoundsVisitor>
#include <osg/Geode>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>

using namespace std;

osg::ref_ptr<osg::Geode> createAxis();
void createBoundingBox(osg::Node* node);
void timer(void);
void initBoundingBoxPosition(osg::MatrixTransform* mt);

int main()
{
    osg::ref_ptr<osg::Node> glider = osgDB::readNodeFile(
            "/usr/share/openscenegraph/data/glider.osg");

    //    vec->set(
    //            glider->getBound().center() *
    //            osg::computeLocalToWorld(
    // glider->getParentalNodePaths()[0]));
    //    float x, y, z;
    //    x = vec->x();
    //    y = vec->y();
    //    z = vec->z();
    //    cout << x << "," << y << "," << z << endl;

    osg::ref_ptr<osg::MatrixTransform> mt =
            new osg::MatrixTransform;
    initBoundingBoxPosition(mt);
    mt->addChild(glider);

    mt->setMatrix(
            osg::Matrix::translate(osg::Vec3(5, 4, 3)));
    mt->setUpdateCallback(new newNodeCallBack());


    osg::ref_ptr<osg::Group> grp = new osg::Group;
    osg::ref_ptr<osg::Geode> axis = createAxis();
    grp->addChild(mt.get());
    grp->addChild(axis);
    osgViewer::Viewer viewer;
    viewer.setSceneData(grp.get());
    return viewer.run();
}
