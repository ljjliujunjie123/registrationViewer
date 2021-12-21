//
// Created by ZZY on 2021/12/16.
//

#include "NodeWrapper.h"

NodeWrapper::NodeWrapper(TestNode& node) {
    _testNode = &node;
    _type = TEST;
    _displayName = node.getDisplayName();
}

const string & NodeWrapper::getDisplayName() const {
    return _displayName;
}

NODE_TYPE NodeWrapper::getType() const {
    return _type;
}

NodeWrapper::NodeWrapper(TestNode node) {
    _testNode = new TestNode(node);
    _type = TEST;
    _displayName = node.getDisplayName();
}

bool NodeWrapper::operator==(const NodeWrapper &rhs) {
    return this->getType() == rhs.getType() && this->getDisplayName() == rhs.getDisplayName()
}

