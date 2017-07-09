#include <osg/Camera>
#include <osgDB/ReadFile>
#include <osgText/Font>
#include <osgText/Text>
#include <osgViewer/Viewer>

osg::Camera* createHUDCamera(
        double left, double right, double bottom,
        double top)
{
    osg::ref_ptr<osg::Camera> camera = new osg::Camera;
    camera->setReferenceFrame(osg::Transform::ABSOLUTE_RF);
    camera->setClearMask(GL_DEPTH_BUFFER_BIT);
    camera->setRenderOrder(osg::Camera::POST_RENDER);
    camera->setProjectionMatrix(
            osg::Matrix::ortho2D(left, right, bottom, top));
    return camera.release();
}

osgText::Text* createText(
        const osg::Vec3& pos, const std::string& content,
        float size)
{
    osg::ref_ptr<osgText::Font> g_font =
            osgText::readFontFile(
                    "/home/mengyu/material/data/fonts/"
                    "times.ttf");
    osg::ref_ptr<osgText::Text> text = new osgText::Text;
    text->setFont(g_font.get());
    text->setCharacterSize(size);
    text->setAxisAlignment(osgText::TextBase::XY_PLANE);
    text->setPosition(pos);
    text->setText(content);
    return text.release();
}

int main()
{
    osg::ref_ptr<osg::Geode> textGeode = new osg::Geode;
    textGeode->addDrawable(createText(
            osg::Vec3(150.f, 500.f, 0.f), "position",
            20.f));
    textGeode->addDrawable(createText(
            osg::Vec3(150.f, 450.f, 0.f), "speed", 20.f));
    osg::Camera* camera = createHUDCamera(0, 1600, 0, 900);
    camera->addChild(textGeode.get());
    camera->getOrCreateStateSet()->setMode(
            GL_LIGHTING, osg::StateAttribute::OFF);
    osg::ref_ptr<osg::Group> root = new osg::Group;
    root->addChild(camera);
    root->addChild(osgDB::readNodeFile(
            "/home/mengyu/material/data/cessna.osg"));
    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    viewer.run();
}
