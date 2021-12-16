//
// Created by ZZY on 2021/12/9.
//

#ifndef REGISTRATIONVIEWER_NODEMANAGER_H
#define REGISTRATIONVIEWER_NODEMANAGER_H
#include "AbsNode.h"
#include "NodeWrapper.h"

class NodeManager {
    //Singleton impl:
private:
    NodeManager()= default;
    ~NodeManager()= default;
    NodeManager(const NodeManager&);
    NodeManager& operator=(const NodeManager&);
public:
    static NodeManager& getInstance(){
        static NodeManager instance;
        return instance;
    }
    //Actual functions:
public:
    void registerNode(NodeWrapper node);
    void unregisterNode(const NodeWrapper& node);
    void findAndUnregisterNode(const string& name);
    const list<NodeWrapper>& getNodes() const;
private:
    list<NodeWrapper> nodes;
};


#endif //REGISTRATIONVIEWER_NODEMANAGER_H
