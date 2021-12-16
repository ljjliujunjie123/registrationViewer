//
// Created by ZZY on 2021/12/9.
//

#ifndef REGISTRATIONVIEWER_NODEMANAGER_H
#define REGISTRATIONVIEWER_NODEMANAGER_H
#include "AbsNode.h"
#include "NodeWrapper.h"

class NodeManager {
public:
    void registerNode(const NodeWrapper& node);
    void unregisterNode(const NodeWrapper& node);
    void findAndUnregisterNode(const string& name);
    list<NodeWrapper>::const_iterator& getNodes() const;
private:
    list<NodeWrapper> nodes;

};


#endif //REGISTRATIONVIEWER_NODEMANAGER_H
