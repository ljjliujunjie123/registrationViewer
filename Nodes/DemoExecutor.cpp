//
// Created by ZZY on 2021/12/28.
//
#include "DemoExecutor.h"




void DemoExecutor::runNode(AbsNode &node, int interval) {
    node.updateProgress(0);
    for (int p = 1; p <= 100; p++){
        this_thread::sleep_for(chrono::milliseconds(interval));
        node.updateProgress(p);
    }
}

void DemoExecutor::executeNode(AbsNode &node) {
    thread executor(runNode, node, 1000);
    executor.join();
}

void DemoExecutor::executeNodes(list<NodeWrapper> &nodes) {
    for(auto& it: nodes){
        executeNode(reinterpret_cast<AbsNode &>(it));
    }
}
