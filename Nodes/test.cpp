//
// Created by ZZY on 2021/12/16.
//

#include "Tests/TestNode.h"
#include "Tests/execution.h"


void testTestNodeArgs();


int main(){
    testTestNodeArgs();
//    TestNode n("test");
//    executeTestNode(n,100);
}

void testTestNodeArgs(){
    TestNode n("test");
    cout<<n.generateArgs()<<endl;
}