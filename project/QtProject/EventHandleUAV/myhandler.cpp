#include "myhandler.h"
#include <osgGA/GUIEventAdapter>

bool MyHandler::handleKeyDown(
        const osgGA::GUIEventAdapter& ea,
        osgGA::GUIActionAdapter& aa)
{
    //    osgViewer::Viewer* viewer =
    //            dynamic_cast<osgViewer::Viewer*>(&aa);
    if (!_model) return false;
    osg::Matrix matrix = _model->getMatrix();
    osg::Vec3 v;
    switch (ea.getKey())
    {
        case 'a':
        case 'A':
            matrix *=
                    osg::Matrix::translate(-1.f, 0.f, 0.f);
            break;
        case 'd':
        case 'D':
            matrix *= osg::Matrix::translate(1.f, 0.f, 0.f);
            break;
        case 'w':
        case 'W':
            matrix *= osg::Matrix::translate(0.f, 1.f, 0.f);
            break;
        case 's':
        case 'S':
            matrix *=
                    osg::Matrix::translate(0.f, -1.f, 0.f);
            break;
        case 'u':
        case 'U':
            matrix *= osg::Matrix::translate(0.f, 0.f, 1.f);
            break;
        case 'n':
        case 'N':
            matrix *=
                    osg::Matrix::translate(0.f, 0.f, -1.f);
            break;
        case osgGA::GUIEventAdapter::KEY_Space:
            flushMouseEventStack();
            _thrown = false;
            home(ea, aa);
            return true;
            break;
        case '1':
            v = getBoundingBoxPosition(_model.get());
            cout << v.x() << " , " << v.y() << " , "
                 << v.z() << endl;
            break;
        default:
            break;
    }
    _model->setMatrix(matrix);
    return false;
}

osg::Vec3 MyHandler::getBoundingBoxPosition(
        osg::MatrixTransform* mt)
{
    osg::BoundingSphere pcenter = mt->getBound();
    osg::Vec3 vec = pcenter.center();

    return vec;
}
