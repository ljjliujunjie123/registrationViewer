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
    void registerNode(NodeWrapper node, const string& listItemDisplay);
    void unregisterNode(const string& listItemDisplay);
    void findAndUnregisterNode(const string& name);
    const map<string, NodeWrapper>& getNodes() const;

    void addShownNode(const AbsNode& node, int index);
    void removeShownNode(int index);
    list<AbsNode>& getShownNodes();
private:
    map<string, NodeWrapper> registeredNodes;
    list<AbsNode> shownNodes;
};

#endif //REGISTRATIONVIEWER_NODEMANAGER_H
