#ifndef VIEWERQT_H
#define VIEWERQT_H

#include "adapterwidget.h"

class ViewerQT : public osgViewer::Viewer,
                 public AdapterWidget
{
public:
    ViewerQT(
            QWidget* parent = 0, const char* name = 0,
            const QGLWidget* shareWidget = 0,
            WindowFlags f = 0);

    virtual void paintGL() { frame(); }

protected:
    QTimer _timer;
};

#endif  // VIEWERQT_H
