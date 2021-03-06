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

const string &AbsNode::getDescription() const {
    return description;
}

void AbsNode::updateProgress(int prog) const {
    if (_NODE_PROGRESS_OUT) cout << "[" << this_thread::get_id() << "]: " << "Update progress " << prog << endl;
    if( prog > 100 || prog < 0) return;
    if(prog == 0) startListener();
    else if ( prog == 100 ) finishListener();
    progressListener(prog);
}



