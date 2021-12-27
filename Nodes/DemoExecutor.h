//
// Created by ZZY on 2021/12/28.
//

#ifndef REGISTRATIONVIEWER_DEMOEXECUTOR_H
#define REGISTRATIONVIEWER_DEMOEXECUTOR_H
#include<thread>
#include<list>
#include "NodeWrapper.h"
#include "AbsNode.h"

namespace DemoExecutor {
    void executeNodes(list<NodeWrapper>& nodes);
    void runNode(AbsNode& node, int interval);
    void executeNode(AbsNode& node);
}

#endif //REGISTRATIONVIEWER_DEMOEXECUTOR_H
