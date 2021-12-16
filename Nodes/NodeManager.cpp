//
// Created by ZZY on 2021/12/9.
//

#include "NodeManager.h"

void NodeManager::registerNode(NodeWrapper node) {
    auto it = nodes.begin();
    for(; it != nodes.end(); it++){
        if(it->getDisplayName() == node.getDisplayName() && node.getType() == it->getType()) {
            cout<<"duplicated register of Node"<<node.getType()<<", nameed "<<node.getDisplayName()<<endl;
            return;
        }
    }
    nodes.insert(it, node);
}
