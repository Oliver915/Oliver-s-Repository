#include "createhud_viewpoint.h"

osg::Node* createHUD_viewPoint(osgText::Text* text)
{
    osg::ref_ptr<osgText::Font> font =
            osgText::readFontFile(
                    "/home/lzt/material/data/fonts/"
                    "arial.ttf");
    text->setFont(font);
    osg::Vec3 position(10.0f, 570.0f, 0.0f);
    text->setPosition(position);
    text->setColor(osg::Vec4(1.f, 1.f, 0.f, 1.f));
    text->setText(L"");
    text->setCharacterSize(10.f);
    text->setDataVariance(osg::Object::DYNAMIC);

    osg::Geode* geode = new osg::Geode;
    geode->addDrawable(text);
    osg::StateSet* stateset = geode->getOrCreateStateSet();
    stateset->setMode(
            GL_LIGHTING, osg::StateAttribute::OFF);
    stateset->setMode(
            GL_DEPTH_TEST, osg::StateAttribute::OFF);
    stateset->setMode(GL_BLEND, osg::StateAttribute::ON);

    osg::Camera* camera = new osg::Camera;
    camera->setProjectionMatrix(
            osg::Matrix::ortho2D(0, 600, 0, 600));
    camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
    camera->setViewMatrix(osg::Matrix::identity());
    camera->setClearMask(GL_DEPTH_BUFFER_BIT);
    camera->setAllowEventFocus(false);
    camera->setRenderOrder(osg::Camera::POST_RENDER);
    camera->addChild(geode);
    return camera;
}
