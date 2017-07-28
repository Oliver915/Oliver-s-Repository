#ifndef FIND_NODE_VISITOR_H
#define FIND_NODE_VISITOR_H

#include <iostream>
#include <osg/Node>
#include <osg/NodeVisitor>
#include <osgSim/DOFTransform>
#include <vector>

class findNodeVisitor : public osg::NodeVisitor
{
public:
    findNodeVisitor();
    findNodeVisitor(const std::string& searchName);
    virtual void apply(osg::Node& searchNode);
    virtual void apply(osg::Transform& searchNode);
    void setNameToFind(const std::string& searchName);
    osg::Node* getFirst();
    typedef std::vector<osg::Node*> nodeListType;
    nodeListType& getNodeList() { return foundNodeList; }
private:
    std::string searchForName;
    nodeListType foundNodeList;
};

#endif
