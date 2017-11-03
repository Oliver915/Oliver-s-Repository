#ifndef MPSSIDEVIEWMANIPULATOR_H
#define MPSSIDEVIEWMANIPULATOR_H

#include <osgGA/NodeTrackerManipulator>
#include <osgSim/DOFTransform>

class MpsHUDHandler;

/**
 * @brief The sideOrBehindViewManipulator class
 */
class MpsSideViewManipulator
        : public osgGA::NodeTrackerManipulator
{
public:
    /**
     * @brief MpsSideViewManipulator
     * @param pHandler
     */
    MpsSideViewManipulator(MpsHUDHandler* pHandler);

    /**
     * @brief changeUAVthroughBar
     * @param indexOfUAV
     */
    void changeUAVthroughBar(int indexOfUAV);

    /**
     * @brief clickZoomIn
     * @param dy
     * @param pushForwardIfNeeded
     */
    void clickZoom(
            const float dy, bool pushForwardIfNeeded);

    /**
     * @brief clickSideView
     */
    void clickSideView();

private:
    /**
     * @brief init
     * @param ea
     * @param us
     */
    virtual void init(
            const osgGA::GUIEventAdapter& ea,
            osgGA::GUIActionAdapter& actionAdapter);

    /**
     * @brief handleKeyDown
     * @param eventAdapter
     * @param actionAdapter
     * @return
     */
    bool handleKeyDown(
            const osgGA::GUIEventAdapter& eventAdapter,
            osgGA::GUIActionAdapter& actionAdapter);

    /**
     * @brief handleChangeView
     * @param eventAdapter
     * @param actionAdapter
     * @return
     */
    bool handleChangeView(
            const osgGA::GUIEventAdapter& eventAdapter,
            osgGA::GUIActionAdapter& actionAdapter);

    /**
     * @brief handleFrame
     * @param eventAdapter
     * @param actionAdapter
     * @return
     */
    bool handleFrame(
            const osgGA::GUIEventAdapter& eventAdapter,
            osgGA::GUIActionAdapter& actionAdapter);

    /**
     * @brief setLabel
     * @param name
     */
    void setLabel(const std::string& name);

    /**
     * @brief UpdateText
     * @param doft
     */
    void UpdateText(
            const osgGA::GUIEventAdapter&,
            const osgSim::DOFTransform* doft);

    /**
     * @brief updateXYZ
     * @param uavDOF
     */
    void updateXYZ(
            osg::ref_ptr<osgSim::DOFTransform> uavDOF);

protected:
    // the UAV doft node
    osgSim::DOFTransform* uavDOF;

    // HUDhandler
    MpsHUDHandler* hudHandler;

    // uavDOF's current position
    double x;
    double y;
    double z;

    // rotate flag
    bool rotateFlag;

    // sideView flag
    bool sideViewFlag;
};

#endif  // MPSSIDEVIEWMANIPULATOR_H
