#ifndef CHUD_VIEWPOINT_H
#define CHUD_VIEWPOINT_H

#include <osgGA/GUIEventHandler>
#include <osgText/Text>
#include <osgViewer/Viewer>
#include <sstream>
#include <osg/MatrixTransform>
#include <osgSim/DOFTransform>

using namespace std;

class CHUD_viewPoint : public osgGA::GUIEventHandler
{
public:
    CHUD_viewPoint(
            osgText::Text* updateText,
            osgSim::DOFTransform* doftnode)
        : m_text(updateText)
        , m_model(doftnode)
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
            osgSim::DOFTransform* doft);

protected:
    osg::Vec3 m_vPosUAV;
    osg::ref_ptr<osgText::Text> m_text;
    osg::ref_ptr<osgSim::DOFTransform> m_model;
};

#endif  // CHUD_VIEWPOINT_H
