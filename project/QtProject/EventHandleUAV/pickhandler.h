#ifndef PICKHANDLER_H
#define PICKHANDLER_H

#include <osgGA/GUIEventHandler>
#include <osgSim/DOFTransform>
#include <osgViewer/Viewer>

class PickHandler : public osgGA::GUIEventHandler
{
public:
    PickHandler(osgSim::DOFTransform* pickDof) {
        pickDof=_dofNode;
    }
    ~PickHandler() {}
    bool handle(
            const osgGA::GUIEventAdapter& ea,
            osgGA::GUIActionAdapter& aa);
    virtual void pick(
            osgViewer::Viewer* viewer,
            const osgGA::GUIEventAdapter& ea);

private:
    osgSim::DOFTransform* _dofNode;
};

#endif  // PICKHANDLER_H
