#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Group>
#include <osg/MatrixTransform>

osg::ref_ptr<osg::Node> createGridPlane();
osg::ref_ptr<osg::Node> createText();

osg::ref_ptr<osg::Node> createSceneGraph()
{
    osg::ref_ptr<osg::Group> SceneGraph = new osg::Group();
    osg::ref_ptr<osg::Node> NodeGridPlane =
            createGridPlane();
    osg::ref_ptr<osg::Node> NodeText = createText();
    SceneGraph->addChild(NodeGridPlane);
    SceneGraph->addChild(NodeText);
    return SceneGraph.get();
}
