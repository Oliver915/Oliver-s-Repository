#ifndef MPSTRACKBALLMANIPULATOR_H
#define MPSTRACKBALLMANIPULATOR_H

#include <osgGA/TrackballManipulator>
#include <osgSim/DOFTransform>

class MpsHUDHandler;

/**
 * @brief The osg class which is a event control class
 * (keyboard, mouse, frame events and so on)
 */
class MpsTrackballManipulator
        : public osgGA::TrackballManipulator
{
public:
    /**
     * @brief MpsTrackballManipulator
     * @param pHandler
     */
    MpsTrackballManipulator(MpsHUDHandler* pHandler);
    ~MpsTrackballManipulator() {}

    /**
     * @brief handleKeyDown
     * @param ea
     * @param aa
     * @return
     */
    virtual bool handleKeyDown(
            const osgGA::GUIEventAdapter& ea,
            osgGA::GUIActionAdapter& aa);

    /**
     * @brief handleFrame
     * @param ea
     * @param aa
     * @return
     */
    virtual bool handleFrame(
            const osgGA::GUIEventAdapter& ea,
            osgGA::GUIActionAdapter& aa);

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
     * @brief // key A D W S control the yaw and pitch of
     * the view
     * @param eventTimeDelta
     * @param dx
     * @param dy
     * @return
     */
    bool performMovementLeftKey(
            double eventTimeDelta, double dx, double dy);

    /**
     * @brief changeUAVthroughBar
     * @param indexOfUAV
     */
    void changeUAVthroughBar(int indexOfUAV);

protected:
    // the UAV doft node
    osgSim::DOFTransform* uavDOF;

    // HUD handler
    MpsHUDHandler* hudHandler;
};

#endif  // MPSTRACKBALLMANIPULATOR_H
