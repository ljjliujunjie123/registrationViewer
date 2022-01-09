//
// Created by ZZY on 2021/12/9.
//

#include "NodeManager.h"
#include "DemoExecutor.h"

void NodeManager::registerNode(NodeWrapper node, const string& itemDisplay) {
    auto it = registeredNodes.cbegin();
    for(; it != registeredNodes.cend(); it++){
        if(it->first == itemDisplay && node.getType() == it->second.getType()) {
            cout<<"duplicated register of Node"<<node.getType()<<", named "<<node.getDisplayName()<<endl;
            return;
        }
    }
    registeredNodes.insert(make_pair(itemDisplay, node));
}

void NodeManager::unregisterNode(const string& itemDisplay) {
    auto it = registeredNodes.find(itemDisplay);
    if (it != registeredNodes.end())
        registeredNodes.erase(it);
    else cout<<"Requested key not found"<<endl;
}

const map<string, NodeWrapper> &NodeManager::getNodes() const {
    return registeredNodes;
}

void NodeManager::findAndUnregisterNode(const string &name) {
    cout<<"Not implemented"<<endl;
}

list<NodeWrapper> &NodeManager::getShownNodes() {
    return shownNodes;
}

void NodeManager::addShownNode(const NodeWrapper& node, int index) {
    auto it = shownNodes.begin();
    advance(it,index);
    shownNodes.insert(it, node);
}

void NodeManager::removeShownNode(int index) {
    auto it = shownNodes.begin();
    advance(it,index);
    shownNodes.erase(it);
}

void NodeManager::executeCurrentNodes(function<void(string)> fileUpdateListener) {
    DemoExecutor::executeNodes(getInstance().shownNodes, std::ref(fileUpdateListener));

}


