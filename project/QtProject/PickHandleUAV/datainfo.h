#ifndef DATAINFO_H
#define DATAINFO_H

#include <osg/Geode>

class DataInfo : public osg::Referenced
{
public:
    DataInfo();
    osg::Vec3* SetData(float a, float b, float c);
    osg::Vec3* v;
private:
    float a;
    float b;
    float c;
};

#endif  // DATAINFO_H
