#include "trailercallback.h"



void TrailerCallback::operator()(
        osg::Node* node, osg::NodeVisitor* nv)
{
    osgSim::DOFTransform* doft =
            static_cast<osgSim::DOFTransform*>(node);
    osg::Vec3 vec = doft->getCurrentTranslate();
    if (doft && trailerRibbon.valid())
    {
        //取出当前无人机的矩阵、轨迹带的顶点、法线数组
        osg::Matrix matrix = doft->getPutMatrix();

        osg::Vec3Array* vertices =
                static_cast<osg::Vec3Array*>(
                        trailerRibbon->getVertexArray());
        osg::Vec3Array* normals =
                static_cast<osg::Vec3Array*>(
                        trailerRibbon->getNormalArray());

        //更新顶点数组（序号靠前的顶点跟随靠后的顶点,最靠后的顶点坐标为无人机当前位置）
        for (unsigned int i = 0; i < g_numPoints - 3;
             i += 2)
        {
            (*vertices)[i] = (*vertices)[i + 2];
            (*vertices)[i + 1] = (*vertices)[i + 3];
            (*normals)[i] = (*normals)[i + 2];
            (*normals)[i + 1] = (*normals)[i + 3];
        }
        (*vertices)[g_numPoints - 2] =
                osg::Vec3(
                        vec.x(), vec.y() - g_halfWidth,
                        vec.z()) *
                matrix;
        (*vertices)[g_numPoints - 1] =
                osg::Vec3(
                        vec.x(), vec.y() + g_halfWidth,
                        vec.z()) *
                matrix;
        vertices->dirty();

        //更新法线数组
        osg::Vec3 normal =
                osg::Vec3(0.f, 0.f, 1.f) * matrix;
        normal.normalize();
        (*normals)[g_numPoints - 2] = normal;
        (*normals)[g_numPoints - 1] = normal;
        normals->dirty();

        // dirty包围盒（球）
        trailerRibbon->dirtyBound();
    }
    traverse(node, nv);
}
