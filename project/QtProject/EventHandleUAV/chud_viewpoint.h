#ifndef CHUD_VIEWPOINT_H
#define CHUD_VIEWPOINT_H

#include <osgGA/GUIEventHandler>
#include <osgText/Text>
#include <osgViewer/Viewer>
#include <sstream>
#include <osg/MatrixTransform>

using namespace std;

class CHUD_viewPoint : public osgGA::GUIEventHandler
{
public:
    CHUD_viewPoint(
            osgText::Text* updateText,
            osg::MatrixTransform* mtnode)
        : m_text(updateText)
        , m_model(mtnode)
    {
    }

    ~CHUD_viewPoint() {}
    virtual bool handle(
            const osgGA::GUIEventAdapter& ea,
            osgGA::GUIActionAdapter& aa);

    void UpdateText(
            const osg::Vec3f& v, const osgGA::GUIEventAdapter&);

    void setLabel(const std::string& name)
    {
        if (m_text.get())
        {
            m_text->setText(name);
        }
    }
    osg::Vec3 getBoundingBoxPosition(
            osg::MatrixTransform* mt);

protected:
    osg::Vec3 m_vPosUAV;
    osg::ref_ptr<osgText::Text> m_text;
    osg::ref_ptr<osg::MatrixTransform> m_model;
};

#endif  // CHUD_VIEWPOINT_H
