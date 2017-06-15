#include <osg/Geode>
#include <osg/Geometry>
#include <osg/MatrixTransform>

osg::ref_ptr<osg::Node> createGridPlane()
{
    // 创建一个用于保存几何信息的对象
    osg::ref_ptr<osg::Geometry> GeometryPlane = new osg::Geometry;
    // 创建四个顶点的数组
    osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
    GeometryPlane->setVertexArray(v.get());
    v->push_back(osg::Vec3(-100.f, -100.f, 0.f));
    v->push_back(osg::Vec3(100.f, -100.f, 0.f));
    v->push_back(osg::Vec3(100.f, 100.f, 0.f));
    v->push_back(osg::Vec3(-100.f, 100.f, 0.f));
    // 创建四种颜色的数组
    osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array;
    GeometryPlane->setColorArray(c.get());
    GeometryPlane->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
    c->push_back(osg::Vec4(0.f, 0.f, 1.f, 1.f));
    c->push_back(osg::Vec4(0.f, 0.f, 1.f, 1.f));
    c->push_back(osg::Vec4(0.f, 0.f, 1.f, 1.f));
    c->push_back(osg::Vec4(0.f, 0.f, 1.f, 1.f));
    // 为唯一的法线创建一个数组
    osg::ref_ptr<osg::Vec3Array> n = new osg::Vec3Array;
    GeometryPlane->setNormalArray(n.get());
    GeometryPlane->setNormalBinding(osg::Geometry::BIND_OVERALL);
    n->push_back(osg::Vec3(0.f, -1.f, 0.f));
    // 由保存的数据绘制四个顶点的多边形
    GeometryPlane->addPrimitiveSet(new osg::DrawArrays(
            osg::PrimitiveSet::QUADS, 0, 4));
    osg::ref_ptr<osg::Geode> GeodePlane = new osg::Geode;
    GeodePlane->addDrawable(GeometryPlane.get());

    // draw the gird
    osg::ref_ptr<osg::Geode> GeodeGrid = new osg::Geode();
    osg::ref_ptr<osg::Geometry> GeometryGrid =
            new osg::Geometry();
    osg::ref_ptr<osg::Vec3Array> gridv =
            new osg::Vec3Array();
    int i;
    int num = 80;
    for (i = -80; i <= num; i += 20)
    {
        gridv->push_back(osg::Vec3(i, 105.0f, 0.0f));
        gridv->push_back(osg::Vec3(i, -105.0f, 0.0f));
        gridv->push_back(osg::Vec3(105.0f, i, 0.0f));
        gridv->push_back(osg::Vec3(-105.0f, i, 0.0f));
    }
    GeometryGrid->setVertexArray(gridv);
    // vertify the color
    osg::ref_ptr<osg::Vec4Array> colors =
            new osg::Vec4Array;
    colors->push_back(osg::Vec4(0.f, 1.f, 0.f, 1.0f));
    GeometryGrid->setColorArray(colors.get());
    GeometryGrid->setColorBinding(
            osg::Geometry::BIND_OVERALL);
    // vertify the normals
    osg::ref_ptr<osg::Vec3Array> gridnormals =
            new osg::Vec3Array;
    gridnormals->push_back(osg::Vec3(0.0f, -1.0f, 0.0f));
    GeometryGrid->setNormalArray(gridnormals);
    GeometryGrid->setNormalBinding(
            osg::Geometry::BIND_OVERALL);

    GeometryGrid->addPrimitiveSet(new osg::DrawArrays(
            osg::PrimitiveSet::LINES, 0, gridv->size()));
    GeodeGrid->addDrawable(GeometryGrid);
    osg::ref_ptr<osg::StateSet> set = new osg::StateSet();
    set->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
    set->setMode(GL_LINE_SMOOTH, osg::StateAttribute::ON);
    GeodeGrid->setStateSet(set);

    osg::ref_ptr<osg::Group> GridPlane = new osg::Group;
    // 向 Geode 类添加几何体(Drawable)并返回 Geode
    GridPlane->addChild(GeodePlane);
    GridPlane->addChild(GeodeGrid);
    return GridPlane.get();
}
