#include "uav.h"

UAV::UAV() {}
osg::ref_ptr<osg::Node> UAV::CreateGlider(
        int color, string index)
{
    osg::ref_ptr<osg::Node> UAV = osgDB::readNodeFile(
            "/home/lzt/material/rq1b.osg");
    osg::ref_ptr<osg::Image> skin = new osg::Image;
    switch (color)
    {
        case 0:
            skin = osgDB::readImageFile(
                    "/home/lzt/material/data/Images/"
                    "red.png");
            break;
        case 1:
            skin = osgDB::readImageFile(
                    "/home/lzt/material/data/Images/"
                    "blue.png");
            break;
        case 2:
            skin = osgDB::readImageFile(
                    "/home/lzt/material/data/Images/"
                    "green.png");
            break;
        case 3:
            skin = osgDB::readImageFile(
                    "/home/lzt/material/data/Images/"
                    "yellow.png");
            break;
        case 4:
            skin = osgDB::readImageFile(
                    "/home/lzt/material/data/Images/"
                    "pink.png");
            break;
    }

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
    UAV->setStateSet(state.get());
    // text
    osg::ref_ptr<osg::Geode> textGeode = new osg::Geode;
    osg::ref_ptr<osgText::Font> font =
            osgText::readFontFile(
                    "/home/lzt/material/data/fonts/"
                    "arial.ttf");
    osg::ref_ptr<osgText::Text> text = new osgText::Text;
    text->setFont(font.get());

    text->setText(index);
    text->setPosition(osg::Vec3(0.f, 0.f, 10.f));
    text->setAxisAlignment(osgText::Text::SCREEN);
    text->setAlignment(osgText::Text::CENTER_BOTTOM);
    text->setCharacterSize(4.f);
    textGeode->addDrawable(text.get());

    osg::ref_ptr<osgSim::DOFTransform> grp =
            new osgSim::DOFTransform;
    grp->addChild(UAV);
    grp->addChild(textGeode.get());

    grp->setCurrentScale(osg::Vec3(1.f, 1.f, 1.f));
    grp->setMaxHPR(osg::Vec3(
            3.14159 * 2, 3.14159 / 4.0, 3.14159 / 4.0));
    grp->setMinHPR(osg::Vec3(
            -3.14159 * 2, 3.14159 / 4.0, 3.14159 / 4.0));

    return grp;
}
