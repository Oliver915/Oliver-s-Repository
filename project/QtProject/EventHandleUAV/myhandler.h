#ifndef MYHANDLER_H
#define MYHANDLER_H
#include <iostream>
#include <osg/MatrixTransform>
#include <osgGA/GUIActionAdapter>
#include <osgGA/GUIEventAdapter>
#include <osgGA/GUIEventHandler>
#include <osgGA/TrackballManipulator>
#include <osgSim/DOFTransform>
#include <osgText/Text>
#include <osgViewer/Viewer>
#include <sstream>
#include "findnodevisitor.h"

using namespace std;

class MyHandler : public osgGA::TrackballManipulator
{
public:
    MyHandler(osg::Node* node, osgText::Text* text)
        : _model(node)
        , _text(text)
    {
        _uavDOF = new osgSim::DOFTransform;
    }
    ~MyHandler() {}
    virtual bool handleKeyDown(
            const osgGA::GUIEventAdapter& ea,
            osgGA::GUIActionAdapter& aa);
    virtual bool handleFrame(
            const osgGA::GUIEventAdapter& ea,
            osgGA::GUIActionAdapter& aa);
    osg::Vec3 getBoundingBoxPosition(
            osg::MatrixTransform* mt);
    void setLabel(const std::string& name)
    {
        if (_text.get())
        {
            _text->setText(name);
        }
    }
    void UpdateText(
            const osg::Vec3f& v,
            const osgGA::GUIEventAdapter&,
            const osgSim::DOFTransform* doft);

protected:
    osg::ref_ptr<osgText::Text> _text;
    osg::ref_ptr<osg::Node> _model;
    osg::ref_ptr<osgSim::DOFTransform> _uavDOF;
};

#endif  // MYHANDLER_H
