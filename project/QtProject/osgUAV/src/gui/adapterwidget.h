#ifndef ADAPTERWIDGET_H
#define ADAPTERWIDGET_H

#include <QApplication>
#include <QMainWindow>
#include <QtCore/QString>
#include <QtCore/QTimer>
#include <QtGui/QKeyEvent>
#include <QtOpenGL/QGLWidget>
#include <iostream>
#include <osgDB/ReadFile>
#include <osgGA/GUIEventAdapter>
#include <osgViewer/Viewer>

using Qt::WindowFlags;

class AdapterWidget : public QGLWidget
{
public:
    AdapterWidget(
            QWidget* parent = 0, const char* name = 0,
            const QGLWidget* shareWidget = 0,
            WindowFlags f = 0);
    virtual ~AdapterWidget() {}
    osg::ref_ptr<osgViewer::GraphicsWindow>
    getGraphicsWindow()
    {
        return _gw.get();
    }
    const osg::ref_ptr<osgViewer::GraphicsWindow>
    getGraphicsWidow() const
    {
        return _gw.get();
    }

protected:
    void init();
    virtual void resizeGL(int width, int height);
    virtual void keyPressEvent(QKeyEvent* event);
    virtual void keyReleaseEvent(QKeyEvent* event);
    virtual void mousePressEvent(QMouseEvent* event);
    virtual void mouseReleaseEvent(QMouseEvent* event);
    virtual void mouseMoveEvent(QMouseEvent* event);

    osg::ref_ptr<osgViewer::GraphicsWindowEmbedded> _gw;
};

#endif  // ADAPTERWIDGET_H
