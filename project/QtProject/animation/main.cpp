#include <iostream>
#include <osg/MatrixTransform>
#include <osg/PositionAttitudeTransform>
#include <osg/Quat>
#include <osg/io_utils>
#include <osgAnimation/Channel>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
#include <osgAnimation/StackedTransformElement>
#include <osgAnimation/UpdateMatrixTransform>
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

class ScaleCallBack : public osgAnimation::UpdateMatrixTransform
{
public:
    ScaleCallBack()
        : scale(1.0f)

    {
    }

    virtual void operator()(
            osg::Node* node, osg::NodeVisitor* nv)
    {
        osg::MatrixTransform* mt =
                dynamic_cast<osg::MatrixTransform*>(node);
        if (mt)
        {
            mt->setMatrix(osg::Matrix::scale(
                    osg::Vec3(1.f, 1.f, scale)));
            scale += 0.01;
        }

        traverse(node, nv);
    }

private:
    float scale;
};

// class InfoCallBack: public osg::NodeCallback
//{
// public:
//    virtual void operator()(osg::Node* node,
//    osg::NodeVisitor* nv)
//    {
//        osg::PositionAttitudeTransform* pat =
//            dynamic_cast<osg::PositionAttitudeTransform*>(node);

//        if(pat)
//        {
//            double angle = 0.0;
//            osg::Vec3 axis;
//            pat->getAttitude().getRotate(angle, axis);

//            std::cout << "Node is rotate around the axis("
//            << axis << "), "
//                <<osg::RadiansToDegrees(angle) <<
//                "degrees" << std::endl;
//        }

//        traverse(node, nv);
//    }
//};

int main(int argc, char** argv)
{
    osg::ArgumentParser argument(&argc, argv);
    osg::ref_ptr<osg::Geode> GeodeLine = new osg::Geode;
    osg::ref_ptr<osg::Geometry> GeometryLine =
            new osg::Geometry;
    osg::ref_ptr<osg::Vec3Array> vLine = new osg::Vec3Array;
    vLine->push_back(osg::Vec3(0, 0, 0));
    vLine->push_back(osg::Vec3(0, 0, 1));
    GeometryLine->setVertexArray(vLine.get());
    osg::ref_ptr<osg::Vec4Array> cLine = new osg::Vec4Array;
    cLine->push_back(osg::Vec4(0.f, 1.0f, 0.0f, 1.0f));
    GeometryLine->setColorArray(cLine.get());
    GeometryLine->setColorBinding(
            osg::Geometry::BIND_OVERALL);
    GeometryLine->addPrimitiveSet(new osg::DrawArrays(
            osg::PrimitiveSet::LINES, 0, 2));
    GeodeLine->addDrawable(GeometryLine);

    osg::ref_ptr<osg::MatrixTransform> mt =
            new osg::MatrixTransform();
    mt->setName("AnimationNode");
    mt->setDataVariance(osg::Object::DYNAMIC);
    mt->addChild(GeodeLine);

    osg::ref_ptr<ScaleCallBack> scb =new ScaleCallBack();
    scb->setName("AnimationCallBack");
    mt->setUpdateCallback(scb);
    osg::ref_ptr<osgAnimation::Vec3LinearChannel> channel1 =
            new osgAnimation::Vec3LinearChannel();
    scb->getStackedTransforms();
    //    pat->addUpdateCallback(new InfoCallBack() );
    osg::ref_ptr<osg::Group> root = new osg::Group;
    osg::ref_ptr<osg::Geode> axis = createAxis();
    root->addChild(axis);
    root->addChild(mt);

    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    return viewer.run();
}
