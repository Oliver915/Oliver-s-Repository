#ifndef MYHANDLER_H
#define MYHANDLER_H
#include <iostream>
#include <osg/MatrixTransform>
#include <osgGA/GUIActionAdapter>
#include <osgGA/GUIEventAdapter>
#include <osgGA/GUIEventHandler>
#include <osgGA/TrackballManipulator>
#include <osgSim/DOFTransform>
#include <osgViewer/Viewer>
#include "findnodevisitor.h"
using namespace std;

class MyHandler : public osgGA::TrackballManipulator
{
public:
    MyHandler(osg::Node* node)
        : _model(node)
    {
    }

    virtual bool handleKeyDown(
            const osgGA::GUIEventAdapter& ea,
            osgGA::GUIActionAdapter& aa);
    osg::Vec3 getBoundingBoxPosition(
            osg::MatrixTransform* mt);

protected:
    osg::ref_ptr<osg::Node> _model;
};

#endif  // MYHANDLER_H
