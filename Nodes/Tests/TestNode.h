//
// Created by ZZY on 2021/12/16.
//

#ifndef REGISTRATIONVIEWER_TESTNODE_H
#define REGISTRATIONVIEWER_TESTNODE_H
#include "../AbsNode.h"

class TestNode: public AbsNode {
public:
    TestNode(const string& name, const string& desc="");
    const string& generateArgs() const;

private:

};


#endif //REGISTRATIONVIEWER_TESTNODE_H
