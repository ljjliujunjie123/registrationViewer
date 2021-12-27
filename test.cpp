//
// Created by ZZY on 2021/12/16.
//
#ifndef TOPLEVEL_TEST_CPP
#define TOPLEVEL_TEST_CPP

#include "vtkLogoWidget.h"
#include<iostream>
#include<string>

#include "Controls/SpinBoxControl.h"
#include "./Nodes/NodeWrapper.h"
#include "./Nodes/Tests/TestNode.h"
#include "Nodes/NodeManager.h"

using namespace std;


inline void testVtkInteract(){
    vtkLogoWidget* widget;
    cout<<"pass"<<endl;
}

inline void testControlTemplate(){
    SpinBoxControl<int> control(1, "Hello", "", {9,10}, 9);
    if( control.getValue() == 9 ) cout<<"pass"<<endl;
    else cout<<"failed"<<endl;
}

inline void testInitNodeManager(){
    NodeManager& nodeManager = NodeManager::getInstance();
    for (int i = 0; i<10; i++) {
        auto name = "node" + to_string(i);
        auto desc = "node" + to_string(i) + " description";
        auto node = new TestNode(name, desc);
        auto nodeWrapper = new NodeWrapper(*node);
        nodeManager.registerNode(*nodeWrapper, "test nodes");
    }
}

inline void testEntry(){
    cout<<"Testing..."<<endl;
    cout<<"Testing vtkInteract...";
    testVtkInteract();
    cout<<"Testing ControlTemplate...";
    testControlTemplate();
}

#endif // TOPLEVEL_TEST_CPP

