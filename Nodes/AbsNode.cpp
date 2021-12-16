//
// Created by ZZY on 2021/11/30.
//

#include "AbsNode.h"

void AbsNode::addStartListener(function<void(void)> l) {
    startListener = l;
}

void AbsNode::addFinishListener(function<void(void)> l) {
    finishListener = l;
}

void AbsNode::addProgressListener(function<void(int)> l) {
    progressListener = l;
}

void AbsNode::registerUpdateListener(function<void(void)> l) {
    updateListener = l;
}

const string &AbsNode::getDisplayName() const {
    return displayName;
}

AbsNode::AbsNode(const string &name, const string &desc) {

}

