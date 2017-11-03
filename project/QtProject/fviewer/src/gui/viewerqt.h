#ifndef VIEWERQT_H
#define VIEWERQT_H

#include "adapterwidget.h"

/**
 * @brief The ViewerQT class
 */
class ViewerQT : public osgViewer::Viewer,
                 public AdapterWidget
{
public:
    /**
     * @brief ViewerQT
     * @param parent
     * @param shareWidget
     * @param f
     */
    ViewerQT(
            QWidget* parent = 0,
            const QGLWidget* shareWidget = 0,
            WindowFlags f = 0);

    /**
     * @brief paintGL
     */
    virtual void paintGL() { frame(); }
};

#endif  // VIEWERQT_H
