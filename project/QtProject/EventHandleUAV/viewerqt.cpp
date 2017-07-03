#include "viewerqt.h"

ViewerQT::ViewerQT(
        QWidget* parent, const char* name,
        const QGLWidget* shareWidget, WindowFlags f)
    : AdapterWidget(parent, name, shareWidget, f)
{
    getCamera()->setViewport(
            new osg::Viewport(0, 0, width(), height()));
    //创建一个对称的透视投影，有关详细信息，请参阅OpenGL
    // gluPerspective文档.宽高比定义为宽/高。
    getCamera()->setProjectionMatrixAsPerspective(
            30.0f,
            static_cast<double>(width()) /
                    static_cast<double>(height()),
            1.0f, 10000.0f);
    //设置GraphicsContext，提供用于管理与此相机相关联的OpenGL图形上下文的机制。
    getCamera()->setGraphicsContext(getGraphicsWindow());
    //设置渲染遍历将使用的线程模型。
    setThreadingModel(osgViewer::Viewer::SingleThreaded);
    //并且把它的timeout()(定时器超时信号)连接到适当的槽。当这段时间过去了，它将会发射timeout()信号。
    connect(&_timer, SIGNAL(timeout()), this,
            SLOT(updateGL()));
    _timer.start(20);  //使用start()来开始
}
