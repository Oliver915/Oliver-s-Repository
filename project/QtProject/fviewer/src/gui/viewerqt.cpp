#include "viewerqt.h"

ViewerQT::ViewerQT(
        QWidget* parent, const QGLWidget* shareWidget,
        WindowFlags f)
    : AdapterWidget(parent, shareWidget, f)
{
    getCamera()->setViewport(
            new osg::Viewport(0, 0, width(), height()));

    // create a perspective projection
    getCamera()->setProjectionMatrixAsPerspective(
            30.0f, static_cast<double>(width()) /
                           static_cast<double>(height()),
            1.0f, 10000.0f);

    // set the graphicsContext
    getCamera()->setGraphicsContext(getGraphicsWindow());

    // set singleThread
    setThreadingModel(osgViewer::Viewer::SingleThreaded);
}
