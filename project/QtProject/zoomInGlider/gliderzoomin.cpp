#include <osg/MatrixTransform>
#include <osgDB/ReadFile>

osg::ref_ptr<osg::Node> creatNewGlider()
{
    osg::ref_ptr<osg::Node> glider = new osg::Node();
    glider = osgDB::readNodeFile(
            "/home/mengyu/material/data/glider.osg");
    osg::ref_ptr<osg::MatrixTransform> mT =
            new osg::MatrixTransform();
    mT->setMatrix(osg::Matrix::scale(10.0f,10.0f,10.0f));
    mT->addChild(glider);
    return mT.get();
}
