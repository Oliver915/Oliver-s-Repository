#include <osg/Camera>
#include <osg/MatrixTransform>
#include <osgDB/ReadFile>
#include <osgGA/OrbitManipulator>
#include <osgViewer/Viewer>
#include <followupdater.h>
#include <osg/AnimationPath>

using namespace std;

osg::AnimationPathCallback* createAnimationPathCallback(
        double radius, double time)
{
    osg::ref_ptr<osg::AnimationPath> path =
            new osg::AnimationPath;
    path->setLoopMode(osg::AnimationPath::LOOP);

    unsigned int numSamples = 32;
    double delta_yaw =
            2.0f * osg::PI / ((double)numSamples - 1.0f);
    double delta_time = time / (float)numSamples;
    for (unsigned int i = 0; i < numSamples; ++i)
    {
        double yaw = delta_yaw * (double)i;
        osg::Vec3 pos(
                sin(yaw) * radius, cos(yaw) * radius, 0.0f);
        osg::Quat rot(-yaw, osg::Z_AXIS);
        path->insert(
                delta_time * (double)i,
                osg::AnimationPath::ControlPoint(pos, rot));
    }
    osg::ref_ptr<osg::AnimationPathCallback> apcb =
            new osg::AnimationPathCallback;
    apcb->setAnimationPath(path.get());
    return apcb.release();
}

int main(int argc, char* argv[])
{
    //载入无人机模型
    osg::Node* model = osgDB::readNodeFile(
            "/home/lzt/material/data/cessna.osg");
    if (!model) return 1;
    osg::ref_ptr<osg::MatrixTransform> trans =
            new osg::MatrixTransform;
    trans->addUpdateCallback(
            createAnimationPathCallback(100.0f, 20.0));
    trans->addChild(model);

    //载入地形
    osg::ref_ptr<osg::MatrixTransform> terrain =
            new osg::MatrixTransform;
    terrain->addChild(osgDB::readNodeFile(
            "/home/lzt/material/data/lz.osg"));
    terrain->setMatrix(
            osg::Matrix::translate(0.0f, 0.0f, -200.0f));

    osg::ref_ptr<osg::Group> root = new osg::Group;
    root->addChild(trans.get());
    root->addChild(terrain.get());

    osgViewer::Viewer viewer;
    viewer.setSceneData(root.get());
    viewer.addEventHandler(new FollowUpdater(model));

    return viewer.run();
}
