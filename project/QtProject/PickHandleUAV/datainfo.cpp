#include "datainfo.h"

DataInfo::DataInfo() { v = new osg::Vec3; }
osg::Vec3 *DataInfo::SetData(float a, float b, float c)
{
    v->x() = a;
    v->y() = b;
    v->z() = c;
    return v;
}
