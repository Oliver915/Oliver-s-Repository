#include <osg/MatrixTransform>
#include <osgDB/ReadFile>
#include <osgSim/DOFTransform>

osg::ref_ptr<osg::Node> creatNewGlider()
{

    osg::ref_ptr<osg::Node> rq1b = new osg::Node();
    rq1b = osgDB::readNodeFile(
            "/home/lzt/material/rq1b.flt");
    osg::ref_ptr<osgSim::DOFTransform> doft =new osgSim::DOFTransform;
    doft->addChild(rq1b);
    doft->setName("UAV");
    return doft.get();
}
