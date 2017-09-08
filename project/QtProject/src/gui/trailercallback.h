#ifndef TRAILERCALLBACK_H
#define TRAILERCALLBACK_H

#include <osg/Geometry>
#include <osg/NodeCallback>
#include <osgSim/DOFTransform>

// const
const unsigned int g_numPoints = 10000;
const double g_halfWidth = 50.f;

//绘制轨迹线的回调类
class TrailerCallback : public osg::NodeCallback
{
public:
    TrailerCallback(osg::Geometry* ribbon)
        : trailerRibbon(ribbon)
    {
    }

    /**
     * 重写operator函数
     * @brief operator ()
     * @param node
     * @param nv
     */
    virtual void operator()(
            osg::Node* node, osg::NodeVisitor* nv);

protected:
    //轨迹带节点
    osg::observer_ptr<osg::Geometry> trailerRibbon;
};

#endif  // TRAILERCALLBACK_H
