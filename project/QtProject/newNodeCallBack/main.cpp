#include <newnodecallback.h>
#include <stdlib.h>
#include <QCoreApplication>
#include <iostream>
#include <osg/Geode>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
using namespace std;

osg::ref_ptr<osg::Geode> createAxis()
{
    osg::ref_ptr<osg::Geode> geode(new osg::Geode());
    osg::ref_ptr<osg::Geometry> geometry(
            new osg::Geometry());

    osg::ref_ptr<osg::Vec3Array> vertices(
            new osg::Vec3Array());
    vertices->push_back(osg::Vec3(0.0, 0.0, 0.0));
    vertices->push_back(osg::Vec3(10.0, 0.0, 0.0));
    vertices->push_back(osg::Vec3(0.0, 0.0, 0.0));
    vertices->push_back(osg::Vec3(0.0, 10.0, 0.0));
    vertices->push_back(osg::Vec3(0.0, 0.0, 0.0));
    vertices->push_back(osg::Vec3(0.0, 0.0, 10.0));
    geometry->setVertexArray(vertices.get());

    osg::ref_ptr<osg::Vec4Array> colors(
            new osg::Vec4Array());
    colors->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
    colors->push_back(osg::Vec4(1.0f, 0.0f, 0.0f, 1.0f));
    colors->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f));
    colors->push_back(osg::Vec4(0.0f, 1.0f, 0.0f, 1.0f));
    colors->push_back(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f));
    colors->push_back(osg::Vec4(0.0f, 0.0f, 1.0f, 1.0f));
    geometry->setColorArray(
            colors.get(), osg::Array::BIND_PER_VERTEX);
    geometry->addPrimitiveSet(new osg::DrawArrays(
            osg::PrimitiveSet::LINES, 0, 6));

    geode->addDrawable(geometry.get());
    geode->getOrCreateStateSet()->setMode(
            GL_LIGHTING, false);
    return geode;
}
int main(int argc, char** argv)
{
    osg::ref_ptr<osg::Node> glider = osgDB::readNodeFile(
            "/usr/share/openscenegraph/data/glider.osg");
    osg::Vec3* vec = new osg::Vec3;
    vec->set(
            glider->getBound().center() *
            osg::computeLocalToWorld(
                    glider->getParentalNodePaths()[0]));
    float x, y, z;
    x = vec->x();
    y = vec->y();
    z = vec->z();
    cout << x << "," << y << "," << z << endl;

    osg::ref_ptr<osg::MatrixTransform> mt =
            new osg::MatrixTransform;
    mt->addChild(glider);
    mt->setUpdateCallback(new newNodeCallBack(vec));
    osg::ref_ptr<osg::Group> grp = new osg::Group;
    osg::ref_ptr<osg::Geode> axis = createAxis();
    grp->addChild(mt.get());
    grp->addChild(axis);
    osgViewer::Viewer viewer;
    viewer.setSceneData(grp.get());
    return viewer.run();
    delete vec;
}
