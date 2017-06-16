#include <osgText/Font>
#include <osgText/Text>

osg::ref_ptr<osg::Node> createText()
{
    osg::ref_ptr<osg::Geode> GeodeText = new osg::Geode();
    osg::ref_ptr<osgText::Font> font =
            osgText::readFontFile(
                    "/home/mengyu/material/data/fonts/"
                    "arial.ttf");
    osg::Vec4 white(1.f, 1.f, 1.f, 1.f);
    osg::ref_ptr<osgText::Text> text = new osgText::Text();
    text->setFont(font.get());
    text->setColor(white);
    text->setCharacterSize(3.f);
    text->setPosition(osg::Vec3(-4.f, -110.0f, 0.0f));
    text->setText("120E");
    text->setAxisAlignment(osgText::Text::XY_PLANE);
    GeodeText->addDrawable(text.get());
    return GeodeText.get();
}
