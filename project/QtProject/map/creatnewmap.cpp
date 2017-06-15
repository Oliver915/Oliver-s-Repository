#include <osg/Geode>
#include <osg/Geometry>

osg::ref_ptr<osg::Node> createSceneGraph()
{
    // 创建一个用于保存几何信息的对象
    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
    // 创建四个顶点的数组
    osg::ref_ptr<osg::Vec3Array> v = new osg::Vec3Array;
    geom->setVertexArray(v.get());
    v->push_back(osg::Vec3(-100.f, -100.f, 0.f));
    v->push_back(osg::Vec3(100.f, -100.f, 0.f));
    v->push_back(osg::Vec3(100.f, 100.f, 0.f));
    v->push_back(osg::Vec3(-100.f, 100.f, 0.f));
    // 创建四种颜色的数组
    osg::ref_ptr<osg::Vec4Array> c = new osg::Vec4Array;
    geom->setColorArray(c.get());
    geom->setColorBinding(osg::Geometry::BIND_PER_VERTEX);
    c->push_back(osg::Vec4(0.f, 0.f, 1.f, 1.f));
    c->push_back(osg::Vec4(0.f, 0.f, 1.f, 1.f));
    c->push_back(osg::Vec4(0.f, 0.f, 1.f, 1.f));
    c->push_back(osg::Vec4(0.f, 0.f, 1.f, 1.f));
    // 为唯一的法线创建一个数组
    osg::ref_ptr<osg::Vec3Array> n = new osg::Vec3Array;
    geom->setNormalArray(n.get());
    geom->setNormalBinding(osg::Geometry::BIND_OVERALL);
    n->push_back(osg::Vec3(0.f, -1.f, 0.f));
    // 由保存的数据绘制四个顶点的多边形
    geom->addPrimitiveSet(new osg::DrawArrays(
            osg::PrimitiveSet::QUADS, 0, 4));
    // 向 Geode 类添加几何体(Drawable)并返回 Geode
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable(geom.get());
    return geode.get();
}
