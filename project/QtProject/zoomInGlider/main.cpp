#include <iostream>
#include <osg/Notify>
#include <osg/ref_ptr>
#include <osgDB/Registry>
#include <osgDB/WriteFile>

using std::endl;

osg::ref_ptr<osg::Node> creatNewGlider();
int main(int, char**)
{
    osg::ref_ptr<osg::Node> root = creatNewGlider();
    if (!root.valid())
        osg::notify(osg::FATAL)
                << "Failed in createSceneGraph()." << endl;
    bool result = osgDB::writeNodeFile(
            *(root.get()), "gliderZoomIn.osg");
    if (!result)
        osg::notify(osg::FATAL)
                << "Failed in osgDB::writeNode()." << endl;
}
