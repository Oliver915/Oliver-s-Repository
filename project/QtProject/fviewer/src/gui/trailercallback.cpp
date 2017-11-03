#include "trailercallback.h"
#include <osgSim/DOFTransform>

void TrailerCallback::operator()(
        osg::Node* node, osg::NodeVisitor* nv)
{
    osgSim::DOFTransform* doft =
            static_cast<osgSim::DOFTransform*>(node);
    if (doft && trailerRibbon.valid())
    {
        // extract the current matrix,track ribbon's
        // vertices and normal array of the UAV
        osg::Matrix matrix = doft->getPutMatrix();

        osg::Vec3Array* vertices =
                static_cast<osg::Vec3Array*>(
                        trailerRibbon->getVertexArray());
        osg::Vec3Array* normals =
                static_cast<osg::Vec3Array*>(
                        trailerRibbon->getNormalArray());

        // update the vertices array(the former vertices
        // chase the later vertices,the coordinate of the
        // last vertice is located in the position of the
        // UAV)
        for (unsigned int i = 0; i < G_NUM_POINTS - 3;
             i += 2)
        {
            (*vertices)[i] = (*vertices)[i + 2];
            (*vertices)[i + 1] = (*vertices)[i + 3];
            (*normals)[i] = (*normals)[i + 2];
            (*normals)[i + 1] = (*normals)[i + 3];
        }

        osg::Vec3 vec = doft->getCurrentTranslate();
        (*vertices)[G_NUM_POINTS - 2] =
                osg::Vec3(
                        vec.x(), vec.y() - G_HALF_WIDTH,
                        vec.z()) *
                matrix;
        (*vertices)[G_NUM_POINTS - 1] =
                osg::Vec3(
                        vec.x(), vec.y() + G_HALF_WIDTH,
                        vec.z()) *
                matrix;
        vertices->dirty();

        // update the normal array
        osg::Vec3 normal =
                osg::Vec3(0.f, 0.f, 1.f) * matrix;
        normal.normalize();
        (*normals)[G_NUM_POINTS - 2] = normal;
        (*normals)[G_NUM_POINTS - 1] = normal;
        normals->dirty();

        // dirty the boundbox/boundcircle
        trailerRibbon->dirtyBound();
    }

    traverse(node, nv);
}
