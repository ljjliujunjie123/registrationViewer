//
// Created by ZZY on 2021/12/16.
//

#include "NodeWrapper.h"

NodeWrapper::NodeWrapper(TestNode node) {
    _testNode = new TestNode(node);
    _type = TEST;
    _displayName = node.getDisplayName();
}

NodeWrapper::NodeWrapper(AntsAffineRegistrationNode node) {
    _antsAffineNode = new AntsAffineRegistrationNode(node);
    _type = ANTS_TRANSFORM_AFFINE;
    _displayName = node.getDisplayName();
}

NodeWrapper::NodeWrapper(AntsRigidRegistrationNode node) {
    _antsRigidNode = new AntsRigidRegistrationNode(node);
    _type = ANTS_TRANSFORM_RIGID;
    _displayName = node.getDisplayName();
}

NodeWrapper::NodeWrapper(AntsSyNRegistrationNode node) {
    _antsSyNNode = new AntsSyNRegistrationNode(node);
    _type = ANTS_TRANSFORM_SYN;
    _displayName = node.getDisplayName();
}

const string & NodeWrapper::getDisplayName() const {
    return _displayName;
}

NODE_TYPE NodeWrapper::getType() const {
    return _type;
}

bool NodeWrapper::operator==(const NodeWrapper &rhs) {
    return this->getType() == rhs.getType() && this->getDisplayName() == rhs.getDisplayName();
}

