//
// Created by ZZY on 2021/12/16.
//

#include "execution.h"



void runTestNode(const TestNode& node, int interval){
    node.updateProgress(0);
    for (int p = 1; p <= 100; p++){
        this_thread::sleep_for(chrono::milliseconds(interval));
        node.updateProgress(p);
    }
}


void executeTestNode(const TestNode& node, int intervalMilliseconds){
    thread executionThread(runTestNode, node, intervalMilliseconds);
    executionThread.join();
}
