#include "mainwindow.h"

#include <QApplication>
#include<iostream>
#include<string>
#include "./Nodes/NodeWrapper.h"
#include "./Nodes/Tests/TestNode.h"
#include "test.cpp"


using namespace std;


int main(int argc, char *argv[])
{
    testEntry();
    NodeManager& nodeManager = NodeManager::getInstance();
    for (int i = 0; i<10; i++) {
        auto name = "node" + to_string(i);
        auto desc = "node" + to_string(i) + " description";
        auto node = new TestNode(name, desc);
        auto nodeWrapper = new NodeWrapper(*node);
        nodeManager.registerNode(*nodeWrapper);
    }
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}

int hello(){
    std::cout<<"Hello"<<std::endl;
}


