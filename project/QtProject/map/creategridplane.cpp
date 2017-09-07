#include <osg/Geode>
#include <osg/Geometry>
#include <osg/LineWidth>
#include <osg/MatrixTransform>
#include <osg/Multisample>
#include <osg/PolygonOffset>
#include <osgSim/DOFTransform>
osg::ref_ptr<osg::Node> createGridPlane()
{
    // 创建一个用于保存几何信息的对象
    osg::ref_ptr<osg::Geometry> GeometryPlane =
            new osg::Geometry;
    // 创建四个顶点的数组
    osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
    GeometryPlane->setVertexArray(v.get());
    double x1, x2, deX, y1, y2, deY, newX1, newX2, newY1,
            newY2;
    x1 = 4900000;
    x2 = 5000000;
    deX = (x1 + x2) / 2;
    y1 = 1400000;
    y2 = 1500000;
    deY = (y1 + y2) / 2;
    newX1 = x1 - deX;
    newX2 = x2 - deX;
    newY1 = y1 - deY;
    newY2 = y2 - deY;
    v->push_back(osg::Vec3(newX1, newY1, 0.f));
    v->push_back(osg::Vec3(newX2, newY1, 0.f));
    v->push_back(osg::Vec3(newX2, newY2, 0.f));
    v->push_back(osg::Vec3(newX1, newY2, 0.f));
    // 创建四种颜色的数组
    osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array;
    GeometryPlane->setColorArray(c.get());
    GeometryPlane->setColorBinding(
            osg::Geometry::BIND_PER_VERTEX);
    c->push_back(osg::Vec4(0.f, 0.f, 1.f, 0.3));
    c->push_back(osg::Vec4(0.f, 0.f, 1.f, 0.3));
    c->push_back(osg::Vec4(0.f, 0.f, 1.f, 0.3));
    c->push_back(osg::Vec4(0.f, 0.f, 1.f, 0.3));
    // 为唯一的法线创建一个数组
    osg::ref_ptr<osg::Vec3Array> n = new osg::Vec3Array;
    GeometryPlane->setNormalArray(n.get());
    GeometryPlane->setNormalBinding(
            osg::Geometry::BIND_OVERALL);
    n->push_back(osg::Vec3(0.f, -1.f, 0.f));
    // 由保存的数据绘制四个顶点的多边形
    GeometryPlane->addPrimitiveSet(new osg::DrawArrays(
            osg::PrimitiveSet::QUADS, 0, 4));
    osg::ref_ptr<osg::StateSet> SetPlane =
            GeometryPlane->getOrCreateStateSet();
    SetPlane->setMode(GL_BLEND, osg::StateAttribute::ON);
    SetPlane->setMode(
            GL_POLYGON_SMOOTH, osg::StateAttribute::ON);
    SetPlane->setMode(
            GL_DEPTH_TEST, osg::StateAttribute::OFF);
    SetPlane->setMode(
            GL_LIGHTING, osg::StateAttribute::OFF);
    SetPlane->setRenderingHint(
            osg::StateSet::TRANSPARENT_BIN);
    osg::ref_ptr<osg::Geode> GeodePlane = new osg::Geode;
    GeodePlane->addDrawable(GeometryPlane.get());
    GeodePlane->setStateSet(SetPlane);

    // draw the gird
    osg::ref_ptr<osg::Geode> GeodeGrid = new osg::Geode();
    GeodeGrid->setName("grid");
    osg::ref_ptr<osg::Geometry> GeometryGrid =
            new osg::Geometry();
    osg::ref_ptr<osg::Vec3Array> gridv =
            new osg::Vec3Array();
    int num = newY2 - 4000;
    for (int i = newY1 + 4000; i <= num; i += 4000)
    {
        gridv->push_back(osg::Vec3(
                i + (newX1 - newY1), newY2, 0.0f));
        gridv->push_back(osg::Vec3(
                i + (newX1 - newY1), newY1, 0.0f));
        gridv->push_back(osg::Vec3(newX2, i, 0.0f));
        gridv->push_back(osg::Vec3(newX1, i, 0.0f));
    }
    GeometryGrid->setVertexArray(gridv);
    // verify the color
    osg::ref_ptr<osg::Vec4Array> colors =
            new osg::Vec4Array;
    colors->push_back(osg::Vec4(0.1f, 0.9f, 0.9f, 0.25f));
    GeometryGrid->setColorArray(colors.get());
    GeometryGrid->setColorBinding(
            osg::Geometry::BIND_OVERALL);
    // verify the normals
    osg::ref_ptr<osg::Vec3Array> gridnormals =
            new osg::Vec3Array;
    gridnormals->push_back(osg::Vec3(0.0f, 1.f, 0.0f));
    GeometryGrid->setNormalArray(gridnormals);
    GeometryGrid->setNormalBinding(
            osg::Geometry::BIND_OVERALL);

    GeometryGrid->addPrimitiveSet(new osg::DrawArrays(
            osg::PrimitiveSet::LINES, 0, gridv->size()));
    GeodeGrid->addDrawable(GeometryGrid);
    osg::ref_ptr<osg::StateSet> SetGrid =
            new osg::StateSet();
    SetGrid->setMode(GL_DEPTH_TEST,osg::StateAttribute::OFF);
    SetGrid->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
    SetGrid->setMode(
            GL_LINE_SMOOTH, osg::StateAttribute::ON);
    SetGrid->setAttributeAndModes(
            new osg::PolygonOffset(1.0f, 1.0f),
            osg::StateAttribute::ON);
    SetGrid->setRenderingHint(osg::StateSet::TRANSPARENT_BIN);
    osg::ref_ptr<osg::LineWidth> lw =
            new osg::LineWidth(0.01f);
    SetGrid->setAttribute(lw);
    GeodeGrid->setStateSet(SetGrid);

    // Draw z axis
    osg::ref_ptr<osg::Geode> GeodeLine = new osg::Geode;
    osg::ref_ptr<osg::Geometry> GeometryLine =
            new osg::Geometry;
    osg::ref_ptr<osg::Vec3Array> vLine = new osg::Vec3Array;
    vLine->push_back(osg::Vec3(newX1, newY1, 0));
    vLine->push_back(osg::Vec3(newX1, newY1, 2500.f));
    GeometryLine->setVertexArray(vLine.get());
    osg::ref_ptr<osg::Vec4Array> cLine = new osg::Vec4Array;
    cLine->push_back(osg::Vec4(0.f, 0.2f, 0.75f, 0.5f));
    GeometryLine->setColorArray(cLine.get());
    GeometryLine->setColorBinding(
            osg::Geometry::BIND_OVERALL);
    GeometryLine->addPrimitiveSet(new osg::DrawArrays(
            osg::PrimitiveSet::LINES, 0, 2));

    osg::ref_ptr<osg::StateSet> SetLine =
            new osg::StateSet();
    SetLine->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
    SetLine->setMode(
            GL_LINE_SMOOTH, osg::StateAttribute::ON);
    SetLine->setAttributeAndModes(
            new osg::PolygonOffset(1.0f, 1.0f),
            osg::StateAttribute::ON);
    osg::ref_ptr<osg::LineWidth> lwLine =
            new osg::LineWidth(0.01f);
    SetLine->setAttribute(lwLine);
    GeodeGrid->setStateSet(SetLine);

    GeodeLine->addDrawable(GeometryLine);
    // 向 Geode 类添加几何体(Drawable)并返回 Geode

    osg::ref_ptr<osg::Group> GridPlane = new osg::Group;
    GridPlane->addChild(GeodePlane);
    GridPlane->addChild(GeodeGrid);
    GridPlane->addChild(GeodeLine);

    return GridPlane.get();
}
