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
    int interval = 1000;
    auto executor = thread(runNode, std::ref(node), std::cref(interval));
    executor.join();
}

void DemoExecutor::executeNodes(list<NodeWrapper> &nodes, function<void(string)> fileUpdateListener) {
    thread fileWorker(runGetFiles, std::ref(fileUpdateListener));
    for(auto& it: nodes){
//        executeNode(reinterpret_cast<AbsNode &>(it));
    }
    fileWorker.join();
}

void DemoExecutor::runGetFiles(function<void(string)> fileUpdateListener) {
    string path="/Volumes/Samsung_T5/Transfer/ZS18149923/result_1226/";
    auto demoPaths ={"Stage1_level1_Iter0001.nii.gz", "Stage1_level1_Iter0020.nii.gz", "Stage1_level2_Iter0001.nii.gz", "Stage1_level3_Iter0010.nii.gz", "Stage1_level4_Iter0010.nii.gz",
                     "Stage2_level1_Iter0001.nii.gz", "Stage2_level1_Iter0040.nii.gz", "Stage2_level2_Iter0001.nii.gz", "Stage2_level2_Iter0030.nii.gz", "Stage2_level3_Iter0020.nii.gz",
                     "Stage2_level4_Iter0001.nii.gz", "Stage3_level1_Iter0001.nii.gz", "Stage3_level1_Iter0030.nii.gz", "Stage3_level1_Iter0100.nii.gz", "Stage3_level2_Iter0030.nii.gz",
                     "Stage3_level2_Iter0050.nii.gz", "Stage3_level3_Iter0001.nii.gz", "Stage3_level3_Iter0030.nii.gz", "Stage3_level3_Iter0050.nii.gz"};
    for(string item: demoPaths){
        string realPath = path + item;
        fileUpdateListener(realPath);
        this_thread::sleep_for(chrono::milliseconds(10000));
    }
}
