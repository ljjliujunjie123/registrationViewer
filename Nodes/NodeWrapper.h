//
// Created by ZZY on 2021/12/16.
//

#ifndef REGISTRATIONVIEWER_NODEWRAPPER_H
#define REGISTRATIONVIEWER_NODEWRAPPER_H
#include "Tests/TestNode.h"

enum NODE_TYPE{ TEST,
        ANTS_CONFIG,
        ANTS_TRANSFORM_RIGID,
        ANTS_TRANSFORM_AFFINE,
        ANTS_TRANSFROM_BSPLINE,
        ANTS_TRANSFORM_SYN,
        ANTS_TRANFROM_BSPLINESYN
};
class NodeWrapper {
public:
    NODE_TYPE getType();
    const string& getDisplayName();

    NodeWrapper(TestNode& node);
private:
    NODE_TYPE _type;
    string _displayName;
    TestNode* _testNode;
};


#endif //REGISTRATIONVIEWER_NODEWRAPPER_H
