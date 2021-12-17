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
