#include "uav.h"

UAV::UAV() {}

osg::ref_ptr<osg::Node> UAV::CreateGlider(
        /*        float x1, float y1, float z1, float x2, float y2,
        float z2,*/ int a)
{
    osg::ref_ptr<osg::Node> glider = osgDB::readNodeFile(
            "/home/mengyu/material/"
            "gliderZoomIn10.osg");
    osg::ref_ptr<osg::Image> skin = new osg::Image;
    switch (a)
    {
        case 0:
            skin = osgDB::readImageFile(
                    "/home/mengyu/material/data/Images/"
                    "red.png");
            break;
        case 1:
            skin = osgDB::readImageFile(
                    "/home/mengyu/material/data/Images/"
                    "blue.png");
            break;
        case 2:
            skin = osgDB::readImageFile(
                    "/home/mengyu/material/data/Images/"
                    "green.png");
            break;
        case 3:
            skin = osgDB::readImageFile(
                    "/home/mengyu/material/data/Images/"
                    "yellow.png");
            break;
        case 4:
            skin = osgDB::readImageFile(
                    "/home/mengyu/material/data/Images/"
                    "pink.png");
            break;
    }

    //    GliderTrans = new
    //    osg::PositionAttitudeTransform();
    //    GLiderPath = new osg::AnimationPath;
    //    GLiderPath->insert(
    //            0, osg::AnimationPath::ControlPoint(
    //                       osg::Vec3(x1, y1, z1)));
    //    GLiderPath->insert(
    //            20, osg::AnimationPath::ControlPoint(
    //                        osg::Vec3(x2, y2, z2)));
    //    GliderTrans->setUpdateCallback(
    //            new osg::AnimationPathCallback(
    //                    GLiderPath, 0.0, 1.0));
    osg::ref_ptr<osg::Texture2D> texture =
            new osg::Texture2D;
    texture->setImage(skin.get());
    osg::ref_ptr<osg::TexGen> texgen = new osg::TexGen();
    texgen->setMode(osg::TexGen::SPHERE_MAP);
    osg::ref_ptr<osg::TexEnv> texenv = new osg::TexEnv();
    texenv->setMode(osg::TexEnv::Mode::ADD);
    texenv->setColor(osg::Vec4(0.6, 0.6, 0.6, 0.0));
    osg::ref_ptr<osg::StateSet> state = new osg::StateSet;
    state->setTextureAttributeAndModes(
            1, texture.get(), osg::StateAttribute::ON);
    state->setTextureAttributeAndModes(
            1, texgen.get(), osg::StateAttribute::ON);
    state->setTextureAttributeAndModes(1, texenv.get());
    glider->setStateSet(state.get());
    // text
    osg::ref_ptr<osg::Geode> textGeode = new osg::Geode;
    osg::ref_ptr<osgText::Font> font =
            osgText::readFontFile(
                    "/home/mengyu/material/data/fonts/"
                    "arial.ttf");
    osg::ref_ptr<osgText::Text> text = new osgText::Text;
    text->setFont(font.get());
    text->setText("1");
    text->setPosition(osg::Vec3(0.f, 0.f, 10.f));
    text->setAxisAlignment(osgText::Text::SCREEN);
    text->setAlignment(osgText::Text::CENTER_BOTTOM);
    text->setCharacterSize(4.f);
    textGeode->addDrawable(text.get());
    //    GliderTrans->addChild(glider);

    //     Draw line
    // Primite
    //    osg::ref_ptr<osg::Geode> GeodeLine = new
    //    osg::Geode;
    //    osg::ref_ptr<osg::Geometry> GeometryLine =
    //            new osg::Geometry;
    //    osg::ref_ptr<osg::Vec3Array> vLine = new
    //    osg::Vec3Array;
    //    vLine->push_back(osg::Vec3(0, 0, 0));
    //    vLine->push_back(osg::Vec3(0, 0, z1));
    //    GeometryLine->setVertexArray(vLine.get());
    //    osg::ref_ptr<osg::Vec4Array> cLine = new
    //    osg::Vec4Array;
    //    cLine->push_back(osg::Vec4(0.f, 1.0f, 0.0f,
    //    1.0f));
    //    GeometryLine->setColorArray(cLine.get());
    //    GeometryLine->setColorBinding(
    //            osg::Geometry::BIND_OVERALL);
    //    GeometryLine->addPrimitiveSet(new osg::DrawArrays(
    //            osg::PrimitiveSet::LINES, 0, 2));
    //    GeodeLine->addDrawable(GeometryLine);

    //    // position and scale
    //    osg::ref_ptr<osg::MatrixTransform> mt =
    //            new osg::MatrixTransform();
    //    mt->setName("AnimatedNode");
    //    mt->setDataVariance(osg::Object::DYNAMIC);
    //    mt->addChild(GeodeLine);
    //    osg::ref_ptr<osgAnimation::UpdateMatrixTransform>
    //    umt =
    //            new osgAnimation::UpdateMatrixTransform(
    //                    "AnimatedCallback");
    //    umt->getStackedTransforms().push_back(
    //            new
    //            osgAnimation::StackedScaleElement("scale"));
    //    umt->getStackedTransforms().push_back(
    //            new osgAnimation::StackedTranslateElement(
    //                    "position"));
    //    mt->setUpdateCallback(umt);
    //    // channelScale
    //    osg::ref_ptr<osgAnimation::Vec3LinearChannel>
    //            channelScale =
    //                    new
    //                    osgAnimation::Vec3LinearChannel();
    //    channelScale->setName("scale");
    //    channelScale->setTargetName("AnimatedCallback");
    //    channelScale->getOrCreateSampler()
    //            ->getOrCreateKeyframeContainer()
    //            ->push_back(osgAnimation::Vec3Keyframe(
    //                    0, osg::Vec3(1.f, 1.f, 1.f)));
    //    channelScale->getOrCreateSampler()
    //            ->getOrCreateKeyframeContainer()
    //            ->push_back(osgAnimation::Vec3Keyframe(
    //                    20, osg::Vec3(1.f, 1.f, z2 /
    //                    z1)));
    //    osg::ref_ptr<osgAnimation::Animation> anim1 =
    //            new osgAnimation::Animation;
    //    anim1->addChannel(channelScale);
    //    anim1->setPlayMode(osgAnimation::Animation::LOOP);
    //    // channelPosition
    //    osg::ref_ptr<osgAnimation::Vec3LinearChannel>
    //            channelPosition =
    //                    new
    //                    osgAnimation::Vec3LinearChannel;
    //    channelPosition->setName("position");
    //    channelPosition->setTargetName("AnimatedCallback");
    //    channelPosition->getOrCreateSampler()
    //            ->getOrCreateKeyframeContainer()
    //            ->push_back(osgAnimation::Vec3Keyframe(
    //                    0, osg::Vec3(x1, y1, 0.f)));
    //    channelPosition->getOrCreateSampler()
    //            ->getOrCreateKeyframeContainer()
    //            ->push_back(osgAnimation::Vec3Keyframe(
    //                    20, osg::Vec3(x2, y2, 0.f)));
    //    osg::ref_ptr<osgAnimation::Animation> anim2 =
    //            new osgAnimation::Animation;
    //    anim2->addChannel(channelPosition);
    //    anim2->setPlayMode(osgAnimation::Animation::LOOP);

    //    osg::ref_ptr<osg::Group> LineGroup = new
    //    osg::Group;
    //    osg::ref_ptr<osgAnimation::BasicAnimationManager>
    //    bam =
    //            new osgAnimation::BasicAnimationManager;

    //    osg::ref_ptr<osg::Group> root = new osg::Group;

    //    root->addChild(mt);
    //    LineGroup->addChild(root);
    //    LineGroup->setUpdateCallback(bam);
    //    // register and play the animations
    //    bam->registerAnimation(anim1);
    //    bam->registerAnimation(anim2);
    //    bam->playAnimation(anim1);
    //    bam->playAnimation(anim2);

    // Group
    //    osg::ref_ptr<osg::Group> GliderLine = new
    //    osg::Group;
    //    GliderLine->addChild(GliderTrans);
    //    GliderLine->addChild(LineGroup);
    //    return GliderLine;
    osg::ref_ptr<osg::Group> grp = new osg::Group;
    grp->addChild(glider);
    grp->addChild(textGeode.get());
    return grp;
}
