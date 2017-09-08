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

/**
 * @brief The AdapterWidget class
 */
class AdapterWidget : public QGLWidget
{
public:
    /**
     * @brief AdapterWidget
     * @param parent
     * @param shareWidget
     * @param f
     */
    AdapterWidget(
            QWidget* parent = 0,
            const QGLWidget* shareWidget = 0,
            WindowFlags f = 0);

    virtual ~AdapterWidget() {}

    /**
     * @brief getGraphicsWindow
     * @return
     */
    osg::ref_ptr<osgViewer::GraphicsWindow>
    getGraphicsWindow()
    {
        return _gw.get();
    }

    /**
     * @brief getGraphicsWidow
     * @return
     */
    const osg::ref_ptr<osgViewer::GraphicsWindow>
    getGraphicsWidow() const
    {
        return _gw.get();
    }

protected:
    /**
     * @brief init
     */
    void init();

    /**
     * @brief resizeGL
     * @param width
     * @param height
     */
    virtual void resizeGL(int width, int height);

    /**
     * @brief keyPressEvent
     * @param event
     */
    virtual void keyPressEvent(QKeyEvent* event);

    /**
     * @brief keyReleaseEvent
     * @param event
     */
    virtual void keyReleaseEvent(QKeyEvent* event);

    /**
     * @brief mousePressEvent
     * @param event
     */
    virtual void mousePressEvent(QMouseEvent* event);

    /**
     * @brief mouseReleaseEvent
     * @param event
     */
    virtual void mouseReleaseEvent(QMouseEvent* event);

    /**
     * @brief mouseMoveEvent
     * @param event
     */
    virtual void mouseMoveEvent(QMouseEvent* event);

protected:
    //
    osg::ref_ptr<osgViewer::GraphicsWindowEmbedded> _gw;
};

#endif  // ADAPTERWIDGET_H
