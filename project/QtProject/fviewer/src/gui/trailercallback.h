#ifndef TRAILERCALLBACK_H
#define TRAILERCALLBACK_H

#include <osg/Geometry>
#include <osg/NodeCallback>

// const
const static unsigned int G_NUM_POINTS = 5000;
const static double G_HALF_WIDTH = 50.f;

/**
 * @brief The TrailerCallback class
 */
class TrailerCallback : public osg::NodeCallback
{
public:
    /**
     * @brief TrailerCallback
     * @param ribbon
     */
    TrailerCallback(osg::Geometry* ribbon)
        : trailerRibbon(ribbon)
    {
    }

    /**
     * overwrite operator()
     * @brief operator ()
     * @param node
     * @param nv
     */
    virtual void operator()(
            osg::Node* node, osg::NodeVisitor* nv);

protected:
    // the track ribbon node
    osg::observer_ptr<osg::Geometry> trailerRibbon;
};

#endif  // TRAILERCALLBACK_H
