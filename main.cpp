#include "mainwindow.h"

#include <QApplication>
#include<iostream>
#include<string>
#include "test.cpp"
#include "Nodes/NodeManager.h"


using namespace std;

int hello(){
    std::cout<<"Hello"<<std::endl;
}

void initNodeManager(){
    NodeManager& inst = NodeManager::getInstance();
    inst.registerNode(NodeWrapper(TestNode("test node", "test node desc")), "TestNode in List");
//    auto it = inst.getNodes().cbegin();
//    while (it != inst.getNodes().cend()){
//        cout<<it->first<<" "<<it->second.getDisplayName()<<endl;
//    }
}

int main(int argc, char *argv[])
{
    testEntry();
    initNodeManager();
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}