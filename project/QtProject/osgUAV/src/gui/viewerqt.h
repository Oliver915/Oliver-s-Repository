#ifndef VIEWERQT_H
#define VIEWERQT_H

#include <fstream>
#include <iomanip>
#include <iostream>
#include <osgSim/DOFTransform>
#include "adapterwidget.h"
#include "createhud_viewpoint.h"
#include "google/protobuf/io/zero_copy_stream_impl.h"
#include "mps_coordinate.pb.h"
#include "myhandler.h"
#include "uav.h"

using namespace std;
using google::protobuf::io::IstreamInputStream;
using google::protobuf::io::CodedInputStream;
using google::protobuf::Arena;

class ViewerQT : public osgViewer::Viewer,
                 public AdapterWidget
{
public:
    ViewerQT(
            QWidget* parent = 0, const char* name = 0,
            const QGLWidget* shareWidget = 0,
            WindowFlags f = 0);
    virtual void paintGL() { frame(); }
    //    virtual osgSim::DOFTransform* initModel(
    //            int color, char num[]);
    //    virtual void loadUAV();
    //    virtual void addUAVStoModelRoot(osg::Group*
    //    modelRoot);
    //    virtual void changeUAV(
    //            MpsSPlane* pPlane, osgSim::DOFTransform*
    //            temp);

    // public slots:
    //    void changeUAVdof();

protected:
    QTimer _timer;
    //    osg::ref_ptr<osgSim::DOFTransform> doft;
    //    osg::ref_ptr<osgSim::DOFTransform> doft1;
    //    osg::ref_ptr<osgSim::DOFTransform> doft2;
    //    osg::ref_ptr<osgSim::DOFTransform> doft3;
    //    osg::ref_ptr<osg::Group> modelRoot;
    //    unsigned int NumUAV;
};

#endif  // VIEWERQT_H
