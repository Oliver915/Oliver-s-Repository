#include <iostream>
#include <osg/MatrixTransform>
#include <osg/Quat>
#include <osg/io_utils>
#include <osgAnimation/Animation>
#include <osgAnimation/BasicAnimationManager>
#include <osgAnimation/Channel>
#include <osgAnimation/StackedScaleElement>
#include <osgAnimation/StackedTranslateElement>
#include <osgAnimation/UpdateMatrixTransform>
#include <osgDB/ReadFile>
#include <osgViewer/Viewer>
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
    mt->setName("AnimatedNode");
    mt->setDataVariance(osg::Object::DYNAMIC);
    mt->addChild(GeodeLine);

    osg::ref_ptr<osgAnimation::UpdateMatrixTransform> umt =
            new osgAnimation::UpdateMatrixTransform(
                    "AnimatedCallback");
    umt->getStackedTransforms().push_back(
            new osgAnimation::StackedScaleElement("scale"));
    umt->getStackedTransforms().push_back(
            new osgAnimation::StackedTranslateElement(
                    "position"));
    mt->setUpdateCallback(umt);
    // channelScale
    osg::ref_ptr<osgAnimation::Vec3LinearChannel>
            channelScale =
                    new osgAnimation::Vec3LinearChannel();
    channelScale->setName("scale");
    channelScale->setTargetName("AnimatedCallback");
    channelScale->getOrCreateSampler()
            ->getOrCreateKeyframeContainer()
            ->push_back(osgAnimation::Vec3Keyframe(
                    0, osg::Vec3(1.f, 1.f, 1.f)));
    channelScale->getOrCreateSampler()
            ->getOrCreateKeyframeContainer()
            ->push_back(osgAnimation::Vec3Keyframe(
                    20, osg::Vec3(1.f, 1.f, 10.f)));
    osg::ref_ptr<osgAnimation::Animation> anim1 =
            new osgAnimation::Animation;
    anim1->addChannel(channelScale);
    anim1->setPlayMode(osgAnimation::Animation::LOOP);
    // channelPosition
    osg::ref_ptr<osgAnimation::Vec3LinearChannel>
            channelPosition =
                    new osgAnimation::Vec3LinearChannel;
    channelPosition->setName("position");
    channelPosition->setTargetName("AnimatedCallback");
    channelPosition->getOrCreateSampler()
            ->getOrCreateKeyframeContainer()
            ->push_back(osgAnimation::Vec3Keyframe(
                    0, osg::Vec3(0.f, 0.f, 0.f)));
    channelPosition->getOrCreateSampler()
            ->getOrCreateKeyframeContainer()
            ->push_back(osgAnimation::Vec3Keyframe(
                    20, osg::Vec3(5.f, 5.f, 0.f)));
    osg::ref_ptr<osgAnimation::Animation> anim2 =
            new osgAnimation::Animation;
    anim2->addChannel(channelPosition);
    anim2->setPlayMode(osgAnimation::Animation::LOOP);

    osg::ref_ptr<osg::Group> grp = new osg::Group;
    osg::ref_ptr<osgAnimation::BasicAnimationManager> bam =
            new osgAnimation::BasicAnimationManager;

    osg::ref_ptr<osg::Group> root = new osg::Group;
    osg::ref_ptr<osg::Geode> axis = createAxis();
    root->addChild(axis);
    root->addChild(mt);
    grp->addChild(root);
    grp->setUpdateCallback(bam);
    // register and play the animations
    bam->registerAnimation(anim1);
    bam->registerAnimation(anim2);
    bam->playAnimation(anim1);
    bam->playAnimation(anim2);

    osgViewer::Viewer viewer;
    viewer.setSceneData(grp.get());
    return viewer.run();
}
