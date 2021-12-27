//
// Created by ZZY on 2021/12/16.
//

#ifndef REGISTRATIONVIEWER_TESTNODE_H
#define REGISTRATIONVIEWER_TESTNODE_H
#include "../AbsNode.h"
#include<map>

class TestNode: public AbsNode {

public:

    TestNode(const string& name, const string& desc="");
    string generateArgs() const;

private:
    void initControls();
    void generateCmdLineComposite(const CompositeControl& control, string& s) const;
    void generateCmdLineMultiType(const MultiTypeControl& control, string& s) const;
};


#endif //REGISTRATIONVIEWER_TESTNODE_H
