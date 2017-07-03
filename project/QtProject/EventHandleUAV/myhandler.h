#ifndef MYHANDLER_H
#define MYHANDLER_H
#include <osg/MatrixTransform>
#include <osgGA/GUIActionAdapter>
#include <osgViewer/Viewer>
//#include "datainfo.h"

#include <osgGA/TrackballManipulator>
#include <osgGA/GUIEventHandler>
#include <osgGA/GUIEventAdapter>

class MyHandler : public osgGA::TrackballManipulator
{
public:
    MyHandler(osg::MatrixTransform* node)
        : _model(node)
    {
    }
    virtual bool handleKeyDown(
            const osgGA::GUIEventAdapter& ea,
            osgGA::GUIActionAdapter& aa);

protected:
    osg::ref_ptr<osg::MatrixTransform> _model;
};

#endif  // MYHANDLER_H
