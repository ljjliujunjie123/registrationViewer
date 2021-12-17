//
// Created by ZZY on 2021/12/16.
//

#include "Tests/TestNode.h"


void testTestNodeArgs();


int main(){
    testTestNodeArgs();
}

void testTestNodeArgs(){
    TestNode n("test");
    cout<<n.generateArgs()<<endl;
}