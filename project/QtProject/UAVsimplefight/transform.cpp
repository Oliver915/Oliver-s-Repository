#include "transform.h"

Transform::Transform() {}
osg::ref_ptr<osg::Node> Transform::CreateGlider(
        float x1, float y1, float z1, float x2, float y2,
        float z2, int a)
{
    osg::ref_ptr<osg::Node> glider = osgDB::readNodeFile(
            "/home/mengyu/material/"
            "gliderZoomIn.osg");
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

    GliderTrans = new osg::PositionAttitudeTransform();
    GLiderPath = new osg::AnimationPath;
    GLiderPath->insert(
            0, osg::AnimationPath::ControlPoint(
                       osg::Vec3(x1, y1, z1)));
    GLiderPath->insert(
            20, osg::AnimationPath::ControlPoint(
                        osg::Vec3(x2, y2, z2)));
    GliderTrans->setUpdateCallback(
            new osg::AnimationPathCallback(
                    GLiderPath, 0.0, 1.0));
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

    GliderTrans->addChild(glider);
    return GliderTrans;
}
