#include <iostream>
#include <osg/Notify>
#include <osg/ref_ptr>
#include <osgDB/Registry>
#include <osgDB/WriteFile>

using std::endl;

osg::ref_ptr<osg::Node> createSceneGraph();
int main(int, char**)
{
    osg::ref_ptr<osg::Node> root = createSceneGraph();
    if (!root.valid())
        osg::notify(osg::FATAL)
                << "Failed in createSceneGraph()." << endl;
    bool result = osgDB::writeNodeFile(
            *(root.get()), "Simple.osg");
    if (!result)
        osg::notify(osg::FATAL)
                << "Failed in osgDB::writeNode()." << endl;
}
