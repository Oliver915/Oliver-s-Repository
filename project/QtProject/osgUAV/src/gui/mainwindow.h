#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <osgViewer/ViewerEventHandlers>
#include <string>
#include "math.h"
#include "ui_mainwindow.h"
#include "viewerqt.h"
using namespace std;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = 0);
    ~MainWindow();
    virtual osgSim::DOFTransform* initModel(
            int color, string index);
    virtual void loadUAV();
    virtual void addUAVStoModelRoot(osg::Group* modelRoot);
    virtual void changeUAV(
            MpsSPlane* pPlane, osgSim::DOFTransform* temp);

public slots:
    void changeUAVdof();

private:
    Ui::MainWindow* ui;
    QTimer _timer;
    osgSim::DOFTransform* doft;
    osgSim::DOFTransform* doft1;
    osgSim::DOFTransform* doft2;
    osgSim::DOFTransform* doft3;
    osg::Group* modelRoot;
    osgSim::DOFTransform* temp;
    unsigned int NumUAV;
    IstreamInputStream* pIStream;
    CodedInputStream* pCodeStream;
    ifstream iReader;
};

#endif  // MAINWINDOW_H
